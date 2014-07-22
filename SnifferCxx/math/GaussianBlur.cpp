//
//  GaussianBlur.cpp
//  SnifferCxx
//
//  Created by Ke Ding  on 7/21/14.
//  Copyright (c) 2014 JPL. All rights reserved.
//

#include "GaussianBlur.h"
#include <math.h>
#include "../model/Cells.h"
#include "../model/Map3D.h"

namespace Math {
    using namespace std;
    using namespace Model;
    
    /**
     * \brief Fast 3D Gaussian convolution IIR approximation
     * \param volume the data volume, modified in-place
     * \param width, height, depth the data dimensions
     * \param sigma the standard deviation of the Gaussian in pixels
     * \param numsteps number of timesteps, more steps implies better accuracy
     *
     * Implements the fast Gaussian convolution algorithm of Alvarez and Mazorra,
     * where the Gaussian is approximated by a cascade of first-order infinite
     * impulsive response (IIR) filters.  Boundaries are handled with half-sample
     * symmetric extension.
     *
     * Gaussian convolution is approached as approximating the heat equation and
     * each timestep is performed with an efficient recursive computation.  Using
     * more steps yields a more accurate approximation of the Gaussian.  A
     * reasonable default value for \c numsteps is 4.
     *
     * The data is assumed to be ordered such that
     *   volume[x + width*(y + height*z)] = data value at (x,y,z).
     *
     * Reference:
     * Alvarez, Mazorra, "Signal and Image Restoration using Shock Filters and
     * Anisotropic Diffusion," SIAM J. on Numerical Analysis, vol. 31, no. 2,
     * pp. 590-605, 1994.
     */
    void GaussianBlur::gaussianiir3d(double *volume, long width, long height, long depth, double sigma, int numsteps /* = 4*/)
    {
        const long plane = width*height;
        const long numel = plane*depth;
        double lambda, dnu;
        double nu, boundaryscale, postscale;
        double *ptr;
        long i, x, y, z;
        int step;
        
        if(sigma <= 0 || numsteps < 0)
            return;
        
        lambda = (sigma*sigma)/(2.0*numsteps);
        dnu = (1.0 + 2.0*lambda - sqrt(1.0 + 4.0*lambda))/(2.0*lambda);
        nu = (double)dnu;
        boundaryscale = (double)(1.0/(1.0 - dnu));
        postscale = (double)(pow(dnu/lambda,3*numsteps));
        
        /* Filter horizontally along each row */
        for(z = 0; z < depth; z++)
        {
            for(y = 0; y < height; y++)
            {
                for(step = 0; step < numsteps; step++)
                {
                    ptr = volume + width*(y + height*z);
                    ptr[0] *= boundaryscale;
                    
                    /* Filter rightwards */
                    for(x = 1; x < width; x++)
                        ptr[x] += nu*ptr[x - 1];
                    
                    ptr[x = width - 1] *= boundaryscale;
                    
                    /* Filter leftwards */
                    for(; x > 0; x--)
                        ptr[x - 1] += nu*ptr[x];
                }
            }
        }
        
        /* Filter vertically along each column */
        for(z = 0; z < depth; z++)
        {
            for(x = 0; x < width; x++)
            {
                for(step = 0; step < numsteps; step++)
                {
                    ptr = volume + x + plane*z;
                    ptr[0] *= boundaryscale;
                    
                    /* Filter downwards */
                    for(i = width; i < plane; i += width)
                        ptr[i] += nu*ptr[i - width];
                    
                    ptr[i = plane - width] *= boundaryscale;
                    
                    /* Filter upwards */
                    for(; i > 0; i -= width)
                        ptr[i - width] += nu*ptr[i];
                }
            }
        }
        
        /* Filter along z-dimension */
        for(y = 0; y < height; y++)
        {
            for(x = 0; x < width; x++)
            {
                for(step = 0; step < numsteps; step++)
                {
                    ptr = volume + x + width*y;
                    ptr[0] *= boundaryscale;
                    
                    for(i = plane; i < numel; i += plane)
                        ptr[i] += nu*ptr[i - plane];
                    
                    ptr[i = numel - plane] *= boundaryscale;
                    
                    for(; i > 0; i -= plane)
                        ptr[i - plane] += nu*ptr[i];
                }
            }
        }
        
        for(i = 0; i < numel; i++)
            volume[i] *= postscale;
    }
    
    shared_ptr<Cells> GaussianBlur::BlurCells(const Map3D & map, const Coordinate &location, const Cells &cells, size_t step) {
		auto ret_cells = make_shared<Cells>();

		auto locate_x = location[0];
		auto locate_y = location[1];
		auto locate_z = location[2];
		auto size = step * 2 + 1;

		auto index = 0;
		unique_ptr<double[]> arr(new double[size * size * size]);
		for (int h = -step; h < -step + size; h++)  {
			for (int w = -step; w < -step + size; w++) {
				for (int l = -step; l < -step + size; l++){
					auto cell_x = locate_x + l;
					auto cell_y = locate_y + w;
					auto cell_z = locate_z + h;

					auto cell = cells.getCell(cell_x, cell_y, cell_z);
					if (cell) {
						arr[index++] = cell->getMethane().getParticleNum();
					}
					else {
						arr[index++] = 0;
					}
				}
			}
        }

		index = 0;
		gaussianiir3d(arr.get(), size, size, size, step);
		for (int h = -step; h < -step + size; h++)  {
			for (int w = -step; w < -step + size; w++) {
				for (int l = -step; l < -step + size; l++){
					auto cell_x = locate_x + l;
					auto cell_y = locate_y + w;
					auto cell_z = locate_z + h;

					auto bluredVal = arr[index++];
					if (bluredVal > 0) { 	
						Coordinate coord(cell_x, cell_y, cell_z);
						if (map.insideMap(coord)) {
							auto newCell = map.getCell(coord);
							newCell.setMethaneConcentration(bluredVal);
							ret_cells->updateCell(newCell);
						}
					}
				}
			}
		}

		return ret_cells;
    }
}
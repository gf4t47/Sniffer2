from palm.palm import ProtoBase, is_string, RepeatedSequence, ProtoValueError

_PB_type = type
_PB_finalizers = []


# Enumeration: CellTag

Air = 1

Ground = 2

Building = 3

TYPE_CellTag = ProtoBase.TYPE_int32

_CellTag__map = {3: 'Building', 2: 'Ground', 1: 'Air'}

@classmethod
def get_CellTag_name(cls, v):
    return cls._CellTag__map[v]

class Coordinate(ProtoBase):
    _required = [1, 2, 3]
    _field_map = {'coord_y': 2, 'coord_x': 1, 'coord_z': 3}
    
    def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
        self._pbf_parent_callback = _pbf_parent_callback
        self._cache = {}
        self._pbf_establish_parent_callback = None
        ProtoBase.__init__(self, _pbf_buf, **kw)

    @classmethod
    def _pbf_finalize(cls):
        for c in cls._pbf_finalizers:
            c(cls)
        del cls._pbf_finalizers

    @classmethod
    def fields(cls):
        return ['coord_x', 'coord_y', 'coord_z']

    def modified(self):
        return self._evermod

    def __contains__(self, item):
        try:
            return getattr(self, '%s__exists' % item)
        except AttributeError:
            return False

    _pbf_strings = []
    _pbf_finalizers = []

    def __str__(self):
        return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                          if getattr(self, '%s__exists' % f))

    def _get_coord_x(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, ProtoBase.TYPE_int32, 'coord_x')
            self._cache[1] = r
        return r

    def _establish_parentage_coord_x(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_coord_x), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_coord_x
                v._pbf_establish_parent_callback = self._establish_parentage_coord_x

    def _set_coord_x(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_coord_x(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field coord_x"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = ProtoBase.TYPE_int32

    def _mod_coord_x(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = ProtoBase.TYPE_int32

    def _del_coord_x(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "coord_x"

    coord_x = property(_get_coord_x, _set_coord_x, _del_coord_x)

    @property
    def coord_x__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def coord_x__type(self):
        return ProtoBase.TYPE_int32

    def _finalize_coord_x(cls):
        if is_string(ProtoBase.TYPE_int32):
            cls._pbf_strings.append(1)
        elif _PB_type(ProtoBase.TYPE_int32) is _PB_type:
            assert issubclass(ProtoBase.TYPE_int32, RepeatedSequence)
            if is_string(ProtoBase.TYPE_int32.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_coord_x)


    def _get_coord_y(self):
        if 2 in self._cache:
            r = self._cache[2]
        else:
            r = self._buf_get(2, ProtoBase.TYPE_int32, 'coord_y')
            self._cache[2] = r
        return r

    def _establish_parentage_coord_y(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_coord_y), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_coord_y
                v._pbf_establish_parent_callback = self._establish_parentage_coord_y

    def _set_coord_y(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_coord_y(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field coord_y"
            raise ProtoValueError(list_assign_error)
        self._cache[2] = v
        self._mods[2] = ProtoBase.TYPE_int32

    def _mod_coord_y(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[2] = ProtoBase.TYPE_int32

    def _del_coord_y(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 2 in self._cache:
            del self._cache[2]
        if 2 in self._mods:
            del self._mods[2]
        self._buf_del(2)

    _pb_field_name_2 = "coord_y"

    coord_y = property(_get_coord_y, _set_coord_y, _del_coord_y)

    @property
    def coord_y__exists(self):
        return 2 in self._mods or self._buf_exists(2)

    @property
    def coord_y__type(self):
        return ProtoBase.TYPE_int32

    def _finalize_coord_y(cls):
        if is_string(ProtoBase.TYPE_int32):
            cls._pbf_strings.append(2)
        elif _PB_type(ProtoBase.TYPE_int32) is _PB_type:
            assert issubclass(ProtoBase.TYPE_int32, RepeatedSequence)
            if is_string(ProtoBase.TYPE_int32.pb_subtype):
                cls._pbf_strings.append(2)

    _pbf_finalizers.append(_finalize_coord_y)


    def _get_coord_z(self):
        if 3 in self._cache:
            r = self._cache[3]
        else:
            r = self._buf_get(3, ProtoBase.TYPE_int32, 'coord_z')
            self._cache[3] = r
        return r

    def _establish_parentage_coord_z(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_coord_z), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_coord_z
                v._pbf_establish_parent_callback = self._establish_parentage_coord_z

    def _set_coord_z(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_coord_z(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field coord_z"
            raise ProtoValueError(list_assign_error)
        self._cache[3] = v
        self._mods[3] = ProtoBase.TYPE_int32

    def _mod_coord_z(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[3] = ProtoBase.TYPE_int32

    def _del_coord_z(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 3 in self._cache:
            del self._cache[3]
        if 3 in self._mods:
            del self._mods[3]
        self._buf_del(3)

    _pb_field_name_3 = "coord_z"

    coord_z = property(_get_coord_z, _set_coord_z, _del_coord_z)

    @property
    def coord_z__exists(self):
        return 3 in self._mods or self._buf_exists(3)

    @property
    def coord_z__type(self):
        return ProtoBase.TYPE_int32

    def _finalize_coord_z(cls):
        if is_string(ProtoBase.TYPE_int32):
            cls._pbf_strings.append(3)
        elif _PB_type(ProtoBase.TYPE_int32) is _PB_type:
            assert issubclass(ProtoBase.TYPE_int32, RepeatedSequence)
            if is_string(ProtoBase.TYPE_int32.pb_subtype):
                cls._pbf_strings.append(3)

    _pbf_finalizers.append(_finalize_coord_z)


TYPE_Coordinate = Coordinate
_PB_finalizers.append('Coordinate')

class Cell(ProtoBase):
    _required = [1, 2, 3, 4]
    _field_map = {'tag': 2, 'mtn': 3, 'wind': 4, 'coord': 1}
    
    def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
        self._pbf_parent_callback = _pbf_parent_callback
        self._cache = {}
        self._pbf_establish_parent_callback = None
        ProtoBase.__init__(self, _pbf_buf, **kw)

    @classmethod
    def _pbf_finalize(cls):
        for c in cls._pbf_finalizers:
            c(cls)
        del cls._pbf_finalizers

    @classmethod
    def fields(cls):
        return ['coord', 'tag', 'mtn', 'wind']

    def modified(self):
        return self._evermod

    def __contains__(self, item):
        try:
            return getattr(self, '%s__exists' % item)
        except AttributeError:
            return False

    _pbf_strings = []
    _pbf_finalizers = []

    def __str__(self):
        return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                          if getattr(self, '%s__exists' % f))
    
    class WindVector(ProtoBase):
        _required = [1, 2, 3]
        _field_map = {'wv_z': 3, 'wv_x': 1, 'wv_y': 2}
        
        def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
            self._pbf_parent_callback = _pbf_parent_callback
            self._cache = {}
            self._pbf_establish_parent_callback = None
            ProtoBase.__init__(self, _pbf_buf, **kw)
    
        @classmethod
        def _pbf_finalize(cls):
            for c in cls._pbf_finalizers:
                c(cls)
            del cls._pbf_finalizers
    
        @classmethod
        def fields(cls):
            return ['wv_x', 'wv_y', 'wv_z']
    
        def modified(self):
            return self._evermod
    
        def __contains__(self, item):
            try:
                return getattr(self, '%s__exists' % item)
            except AttributeError:
                return False
    
        _pbf_strings = []
        _pbf_finalizers = []
    
        def __str__(self):
            return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                              if getattr(self, '%s__exists' % f))
        
        def _get_wv_x(self):
            if 1 in self._cache:
                r = self._cache[1]
            else:
                r = self._buf_get(1, ProtoBase.TYPE_double, 'wv_x')
                self._cache[1] = r
            return r
    
        def _establish_parentage_wv_x(self, v):
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                if v._pbf_parent_callback:
                    assert (v._pbf_parent_callback == self._mod_wv_x), "subobjects can only have one parent--use copy()?"
                else:
                    v._pbf_parent_callback = self._mod_wv_x
                    v._pbf_establish_parent_callback = self._establish_parentage_wv_x
    
        def _set_wv_x(self, v, modifying=True):
            self._evermod = modifying or self._evermod
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                self._establish_parentage_wv_x(v)
            elif isinstance(v, list):
                list_assign_error = "Can't assign list to repeated field wv_x"
                raise ProtoValueError(list_assign_error)
            self._cache[1] = v
            self._mods[1] = ProtoBase.TYPE_double
    
        def _mod_wv_x(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            self._mods[1] = ProtoBase.TYPE_double
    
        def _del_wv_x(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if 1 in self._cache:
                del self._cache[1]
            if 1 in self._mods:
                del self._mods[1]
            self._buf_del(1)
    
        _pb_field_name_1 = "wv_x"
    
        wv_x = property(_get_wv_x, _set_wv_x, _del_wv_x)
    
        @property
        def wv_x__exists(self):
            return 1 in self._mods or self._buf_exists(1)
    
        @property
        def wv_x__type(self):
            return ProtoBase.TYPE_double
    
        def _finalize_wv_x(cls):
            if is_string(ProtoBase.TYPE_double):
                cls._pbf_strings.append(1)
            elif _PB_type(ProtoBase.TYPE_double) is _PB_type:
                assert issubclass(ProtoBase.TYPE_double, RepeatedSequence)
                if is_string(ProtoBase.TYPE_double.pb_subtype):
                    cls._pbf_strings.append(1)
    
        _pbf_finalizers.append(_finalize_wv_x)
    
        
        def _get_wv_y(self):
            if 2 in self._cache:
                r = self._cache[2]
            else:
                r = self._buf_get(2, ProtoBase.TYPE_double, 'wv_y')
                self._cache[2] = r
            return r
    
        def _establish_parentage_wv_y(self, v):
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                if v._pbf_parent_callback:
                    assert (v._pbf_parent_callback == self._mod_wv_y), "subobjects can only have one parent--use copy()?"
                else:
                    v._pbf_parent_callback = self._mod_wv_y
                    v._pbf_establish_parent_callback = self._establish_parentage_wv_y
    
        def _set_wv_y(self, v, modifying=True):
            self._evermod = modifying or self._evermod
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                self._establish_parentage_wv_y(v)
            elif isinstance(v, list):
                list_assign_error = "Can't assign list to repeated field wv_y"
                raise ProtoValueError(list_assign_error)
            self._cache[2] = v
            self._mods[2] = ProtoBase.TYPE_double
    
        def _mod_wv_y(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            self._mods[2] = ProtoBase.TYPE_double
    
        def _del_wv_y(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if 2 in self._cache:
                del self._cache[2]
            if 2 in self._mods:
                del self._mods[2]
            self._buf_del(2)
    
        _pb_field_name_2 = "wv_y"
    
        wv_y = property(_get_wv_y, _set_wv_y, _del_wv_y)
    
        @property
        def wv_y__exists(self):
            return 2 in self._mods or self._buf_exists(2)
    
        @property
        def wv_y__type(self):
            return ProtoBase.TYPE_double
    
        def _finalize_wv_y(cls):
            if is_string(ProtoBase.TYPE_double):
                cls._pbf_strings.append(2)
            elif _PB_type(ProtoBase.TYPE_double) is _PB_type:
                assert issubclass(ProtoBase.TYPE_double, RepeatedSequence)
                if is_string(ProtoBase.TYPE_double.pb_subtype):
                    cls._pbf_strings.append(2)
    
        _pbf_finalizers.append(_finalize_wv_y)
    
        
        def _get_wv_z(self):
            if 3 in self._cache:
                r = self._cache[3]
            else:
                r = self._buf_get(3, ProtoBase.TYPE_double, 'wv_z')
                self._cache[3] = r
            return r
    
        def _establish_parentage_wv_z(self, v):
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                if v._pbf_parent_callback:
                    assert (v._pbf_parent_callback == self._mod_wv_z), "subobjects can only have one parent--use copy()?"
                else:
                    v._pbf_parent_callback = self._mod_wv_z
                    v._pbf_establish_parent_callback = self._establish_parentage_wv_z
    
        def _set_wv_z(self, v, modifying=True):
            self._evermod = modifying or self._evermod
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                self._establish_parentage_wv_z(v)
            elif isinstance(v, list):
                list_assign_error = "Can't assign list to repeated field wv_z"
                raise ProtoValueError(list_assign_error)
            self._cache[3] = v
            self._mods[3] = ProtoBase.TYPE_double
    
        def _mod_wv_z(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            self._mods[3] = ProtoBase.TYPE_double
    
        def _del_wv_z(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if 3 in self._cache:
                del self._cache[3]
            if 3 in self._mods:
                del self._mods[3]
            self._buf_del(3)
    
        _pb_field_name_3 = "wv_z"
    
        wv_z = property(_get_wv_z, _set_wv_z, _del_wv_z)
    
        @property
        def wv_z__exists(self):
            return 3 in self._mods or self._buf_exists(3)
    
        @property
        def wv_z__type(self):
            return ProtoBase.TYPE_double
    
        def _finalize_wv_z(cls):
            if is_string(ProtoBase.TYPE_double):
                cls._pbf_strings.append(3)
            elif _PB_type(ProtoBase.TYPE_double) is _PB_type:
                assert issubclass(ProtoBase.TYPE_double, RepeatedSequence)
                if is_string(ProtoBase.TYPE_double.pb_subtype):
                    cls._pbf_strings.append(3)
    
        _pbf_finalizers.append(_finalize_wv_z)
    
        
    TYPE_WindVector = WindVector
    _PB_finalizers.append('Cell.WindVector')
    
    TYPE_WindVector = WindVector
    
    class Wind(ProtoBase):
        _required = [1, 2]
        _field_map = {'potential': 2, 'wind': 1}
        
        def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
            self._pbf_parent_callback = _pbf_parent_callback
            self._cache = {}
            self._pbf_establish_parent_callback = None
            ProtoBase.__init__(self, _pbf_buf, **kw)
    
        @classmethod
        def _pbf_finalize(cls):
            for c in cls._pbf_finalizers:
                c(cls)
            del cls._pbf_finalizers
    
        @classmethod
        def fields(cls):
            return ['wind', 'potential']
    
        def modified(self):
            return self._evermod
    
        def __contains__(self, item):
            try:
                return getattr(self, '%s__exists' % item)
            except AttributeError:
                return False
    
        _pbf_strings = []
        _pbf_finalizers = []
    
        def __str__(self):
            return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                              if getattr(self, '%s__exists' % f))
        
        def _get_wind(self):
            if 1 in self._cache:
                r = self._cache[1]
            else:
                r = self._buf_get(1, Cell.TYPE_WindVector, 'wind')
                self._cache[1] = r
            return r
    
        def _establish_parentage_wind(self, v):
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                if v._pbf_parent_callback:
                    assert (v._pbf_parent_callback == self._mod_wind), "subobjects can only have one parent--use copy()?"
                else:
                    v._pbf_parent_callback = self._mod_wind
                    v._pbf_establish_parent_callback = self._establish_parentage_wind
    
        def _set_wind(self, v, modifying=True):
            self._evermod = modifying or self._evermod
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                self._establish_parentage_wind(v)
            elif isinstance(v, list):
                list_assign_error = "Can't assign list to repeated field wind"
                raise ProtoValueError(list_assign_error)
            self._cache[1] = v
            self._mods[1] = Cell.TYPE_WindVector
    
        def _mod_wind(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            self._mods[1] = Cell.TYPE_WindVector
    
        def _del_wind(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if 1 in self._cache:
                del self._cache[1]
            if 1 in self._mods:
                del self._mods[1]
            self._buf_del(1)
    
        _pb_field_name_1 = "wind"
    
        wind = property(_get_wind, _set_wind, _del_wind)
    
        @property
        def wind__exists(self):
            return 1 in self._mods or self._buf_exists(1)
    
        @property
        def wind__type(self):
            return Cell.TYPE_WindVector
    
        def _finalize_wind(cls):
            if is_string(Cell.TYPE_WindVector):
                cls._pbf_strings.append(1)
            elif _PB_type(Cell.TYPE_WindVector) is _PB_type:
                assert issubclass(Cell.TYPE_WindVector, RepeatedSequence)
                if is_string(Cell.TYPE_WindVector.pb_subtype):
                    cls._pbf_strings.append(1)
    
        _pbf_finalizers.append(_finalize_wind)
    
        
        def _get_potential(self):
            if 2 in self._cache:
                r = self._cache[2]
            else:
                r = self._buf_get(2, Cell.TYPE_WindVector, 'potential')
                self._cache[2] = r
            return r
    
        def _establish_parentage_potential(self, v):
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                if v._pbf_parent_callback:
                    assert (v._pbf_parent_callback == self._mod_potential), "subobjects can only have one parent--use copy()?"
                else:
                    v._pbf_parent_callback = self._mod_potential
                    v._pbf_establish_parent_callback = self._establish_parentage_potential
    
        def _set_potential(self, v, modifying=True):
            self._evermod = modifying or self._evermod
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                self._establish_parentage_potential(v)
            elif isinstance(v, list):
                list_assign_error = "Can't assign list to repeated field potential"
                raise ProtoValueError(list_assign_error)
            self._cache[2] = v
            self._mods[2] = Cell.TYPE_WindVector
    
        def _mod_potential(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            self._mods[2] = Cell.TYPE_WindVector
    
        def _del_potential(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if 2 in self._cache:
                del self._cache[2]
            if 2 in self._mods:
                del self._mods[2]
            self._buf_del(2)
    
        _pb_field_name_2 = "potential"
    
        potential = property(_get_potential, _set_potential, _del_potential)
    
        @property
        def potential__exists(self):
            return 2 in self._mods or self._buf_exists(2)
    
        @property
        def potential__type(self):
            return Cell.TYPE_WindVector
    
        def _finalize_potential(cls):
            if is_string(Cell.TYPE_WindVector):
                cls._pbf_strings.append(2)
            elif _PB_type(Cell.TYPE_WindVector) is _PB_type:
                assert issubclass(Cell.TYPE_WindVector, RepeatedSequence)
                if is_string(Cell.TYPE_WindVector.pb_subtype):
                    cls._pbf_strings.append(2)
    
        _pbf_finalizers.append(_finalize_potential)
    
        
    TYPE_Wind = Wind
    _PB_finalizers.append('Cell.Wind')
    
    TYPE_Wind = Wind
    
    class Methane(ProtoBase):
        _required = [1]
        _field_map = {'concentration': 1}
        
        def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
            self._pbf_parent_callback = _pbf_parent_callback
            self._cache = {}
            self._pbf_establish_parent_callback = None
            ProtoBase.__init__(self, _pbf_buf, **kw)
    
        @classmethod
        def _pbf_finalize(cls):
            for c in cls._pbf_finalizers:
                c(cls)
            del cls._pbf_finalizers
    
        @classmethod
        def fields(cls):
            return ['concentration']
    
        def modified(self):
            return self._evermod
    
        def __contains__(self, item):
            try:
                return getattr(self, '%s__exists' % item)
            except AttributeError:
                return False
    
        _pbf_strings = []
        _pbf_finalizers = []
    
        def __str__(self):
            return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                              if getattr(self, '%s__exists' % f))
        
        def _get_concentration(self):
            if 1 in self._cache:
                r = self._cache[1]
            else:
                r = self._buf_get(1, ProtoBase.TYPE_double, 'concentration')
                self._cache[1] = r
            return r
    
        def _establish_parentage_concentration(self, v):
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                if v._pbf_parent_callback:
                    assert (v._pbf_parent_callback == self._mod_concentration), "subobjects can only have one parent--use copy()?"
                else:
                    v._pbf_parent_callback = self._mod_concentration
                    v._pbf_establish_parent_callback = self._establish_parentage_concentration
    
        def _set_concentration(self, v, modifying=True):
            self._evermod = modifying or self._evermod
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if isinstance(v, (ProtoBase, RepeatedSequence)):
                self._establish_parentage_concentration(v)
            elif isinstance(v, list):
                list_assign_error = "Can't assign list to repeated field concentration"
                raise ProtoValueError(list_assign_error)
            self._cache[1] = v
            self._mods[1] = ProtoBase.TYPE_double
    
        def _mod_concentration(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            self._mods[1] = ProtoBase.TYPE_double
    
        def _del_concentration(self):
            self._evermod = True
            if self._pbf_parent_callback:
                self._pbf_parent_callback()
            if 1 in self._cache:
                del self._cache[1]
            if 1 in self._mods:
                del self._mods[1]
            self._buf_del(1)
    
        _pb_field_name_1 = "concentration"
    
        concentration = property(_get_concentration, _set_concentration, _del_concentration)
    
        @property
        def concentration__exists(self):
            return 1 in self._mods or self._buf_exists(1)
    
        @property
        def concentration__type(self):
            return ProtoBase.TYPE_double
    
        def _finalize_concentration(cls):
            if is_string(ProtoBase.TYPE_double):
                cls._pbf_strings.append(1)
            elif _PB_type(ProtoBase.TYPE_double) is _PB_type:
                assert issubclass(ProtoBase.TYPE_double, RepeatedSequence)
                if is_string(ProtoBase.TYPE_double.pb_subtype):
                    cls._pbf_strings.append(1)
    
        _pbf_finalizers.append(_finalize_concentration)
    
        
    TYPE_Methane = Methane
    _PB_finalizers.append('Cell.Methane')
    
    TYPE_Methane = Methane

    def _get_coord(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, TYPE_Coordinate, 'coord')
            self._cache[1] = r
        return r

    def _establish_parentage_coord(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_coord), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_coord
                v._pbf_establish_parent_callback = self._establish_parentage_coord

    def _set_coord(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_coord(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field coord"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = TYPE_Coordinate

    def _mod_coord(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = TYPE_Coordinate

    def _del_coord(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "coord"

    coord = property(_get_coord, _set_coord, _del_coord)

    @property
    def coord__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def coord__type(self):
        return TYPE_Coordinate

    def _finalize_coord(cls):
        if is_string(TYPE_Coordinate):
            cls._pbf_strings.append(1)
        elif _PB_type(TYPE_Coordinate) is _PB_type:
            assert issubclass(TYPE_Coordinate, RepeatedSequence)
            if is_string(TYPE_Coordinate.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_coord)


    def _get_tag(self):
        if 2 in self._cache:
            r = self._cache[2]
        else:
            r = self._buf_get(2, TYPE_CellTag, 'tag')
            self._cache[2] = r
        return r

    def _establish_parentage_tag(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_tag), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_tag
                v._pbf_establish_parent_callback = self._establish_parentage_tag

    def _set_tag(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_tag(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field tag"
            raise ProtoValueError(list_assign_error)
        self._cache[2] = v
        self._mods[2] = TYPE_CellTag

    def _mod_tag(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[2] = TYPE_CellTag

    def _del_tag(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 2 in self._cache:
            del self._cache[2]
        if 2 in self._mods:
            del self._mods[2]
        self._buf_del(2)

    _pb_field_name_2 = "tag"

    tag = property(_get_tag, _set_tag, _del_tag)

    @property
    def tag__exists(self):
        return 2 in self._mods or self._buf_exists(2)

    @property
    def tag__type(self):
        return TYPE_CellTag

    def _finalize_tag(cls):
        if is_string(TYPE_CellTag):
            cls._pbf_strings.append(2)
        elif _PB_type(TYPE_CellTag) is _PB_type:
            assert issubclass(TYPE_CellTag, RepeatedSequence)
            if is_string(TYPE_CellTag.pb_subtype):
                cls._pbf_strings.append(2)

    _pbf_finalizers.append(_finalize_tag)


    def _get_mtn(self):
        if 3 in self._cache:
            r = self._cache[3]
        else:
            r = self._buf_get(3, Cell.TYPE_Methane, 'mtn')
            self._cache[3] = r
        return r

    def _establish_parentage_mtn(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_mtn), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_mtn
                v._pbf_establish_parent_callback = self._establish_parentage_mtn

    def _set_mtn(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_mtn(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field mtn"
            raise ProtoValueError(list_assign_error)
        self._cache[3] = v
        self._mods[3] = Cell.TYPE_Methane

    def _mod_mtn(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[3] = Cell.TYPE_Methane

    def _del_mtn(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 3 in self._cache:
            del self._cache[3]
        if 3 in self._mods:
            del self._mods[3]
        self._buf_del(3)

    _pb_field_name_3 = "mtn"

    mtn = property(_get_mtn, _set_mtn, _del_mtn)

    @property
    def mtn__exists(self):
        return 3 in self._mods or self._buf_exists(3)

    @property
    def mtn__type(self):
        return Cell.TYPE_Methane

    def _finalize_mtn(cls):
        if is_string(Cell.TYPE_Methane):
            cls._pbf_strings.append(3)
        elif _PB_type(Cell.TYPE_Methane) is _PB_type:
            assert issubclass(Cell.TYPE_Methane, RepeatedSequence)
            if is_string(Cell.TYPE_Methane.pb_subtype):
                cls._pbf_strings.append(3)

    _pbf_finalizers.append(_finalize_mtn)


    def _get_wind(self):
        if 4 in self._cache:
            r = self._cache[4]
        else:
            r = self._buf_get(4, Cell.TYPE_Wind, 'wind')
            self._cache[4] = r
        return r

    def _establish_parentage_wind(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_wind), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_wind
                v._pbf_establish_parent_callback = self._establish_parentage_wind

    def _set_wind(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_wind(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field wind"
            raise ProtoValueError(list_assign_error)
        self._cache[4] = v
        self._mods[4] = Cell.TYPE_Wind

    def _mod_wind(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[4] = Cell.TYPE_Wind

    def _del_wind(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 4 in self._cache:
            del self._cache[4]
        if 4 in self._mods:
            del self._mods[4]
        self._buf_del(4)

    _pb_field_name_4 = "wind"

    wind = property(_get_wind, _set_wind, _del_wind)

    @property
    def wind__exists(self):
        return 4 in self._mods or self._buf_exists(4)

    @property
    def wind__type(self):
        return Cell.TYPE_Wind

    def _finalize_wind(cls):
        if is_string(Cell.TYPE_Wind):
            cls._pbf_strings.append(4)
        elif _PB_type(Cell.TYPE_Wind) is _PB_type:
            assert issubclass(Cell.TYPE_Wind, RepeatedSequence)
            if is_string(Cell.TYPE_Wind.pb_subtype):
                cls._pbf_strings.append(4)

    _pbf_finalizers.append(_finalize_wind)


TYPE_Cell = Cell
_PB_finalizers.append('Cell')

class Cells(ProtoBase):
    _required = []
    _field_map = {'cell': 1}
    
    def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
        self._pbf_parent_callback = _pbf_parent_callback
        self._cache = {}
        self._pbf_establish_parent_callback = None
        ProtoBase.__init__(self, _pbf_buf, **kw)

    @classmethod
    def _pbf_finalize(cls):
        for c in cls._pbf_finalizers:
            c(cls)
        del cls._pbf_finalizers

    @classmethod
    def fields(cls):
        return ['cell']

    def modified(self):
        return self._evermod

    def __contains__(self, item):
        try:
            return getattr(self, '%s__exists' % item)
        except AttributeError:
            return False

    _pbf_strings = []
    _pbf_finalizers = []

    def __str__(self):
        return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                          if getattr(self, '%s__exists' % f))

    class Repeated_cell(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Cell
        pb_subtype = pb_subtype()


    TYPE_Repeated_cell = Repeated_cell


    @property
    def cell__stream(self):
        if 1 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[1]]
        return self._get_repeated(1, self.TYPE_Repeated_cell, "cell", lazy=True)

    def cell__fast_append(self, value):
        self._append_to_repeated(1, self.TYPE_Repeated_cell, value)

    def _get_cell(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, self.TYPE_Repeated_cell, 'cell')
            self._cache[1] = r
        return r

    def _establish_parentage_cell(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_cell), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_cell
                v._pbf_establish_parent_callback = self._establish_parentage_cell

    def _set_cell(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_cell(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field cell"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = self.TYPE_Repeated_cell

    def _mod_cell(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = self.TYPE_Repeated_cell

    def _del_cell(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "cell"

    cell = property(_get_cell, _set_cell, _del_cell)

    @property
    def cell__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def cell__type(self):
        return self.TYPE_Repeated_cell

    def _finalize_cell(cls):
        if is_string(cls.TYPE_Repeated_cell):
            cls._pbf_strings.append(1)
        elif _PB_type(cls.TYPE_Repeated_cell) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_cell, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_cell.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_cell)


TYPE_Cells = Cells
_PB_finalizers.append('Cells')

class Map(ProtoBase):
    _required = [1, 2]
    _field_map = {'cell': 3, 'startIndex': 1, 'boundary': 2}
    
    def __init__(self, _pbf_buf='', _pbf_parent_callback=None, **kw):
        self._pbf_parent_callback = _pbf_parent_callback
        self._cache = {}
        self._pbf_establish_parent_callback = None
        ProtoBase.__init__(self, _pbf_buf, **kw)

    @classmethod
    def _pbf_finalize(cls):
        for c in cls._pbf_finalizers:
            c(cls)
        del cls._pbf_finalizers

    @classmethod
    def fields(cls):
        return ['startIndex', 'boundary', 'cell']

    def modified(self):
        return self._evermod

    def __contains__(self, item):
        try:
            return getattr(self, '%s__exists' % item)
        except AttributeError:
            return False

    _pbf_strings = []
    _pbf_finalizers = []

    def __str__(self):
        return '\n'.join('%s: %s' % (f, repr(getattr(self, '_get_%s' % f)())) for f in self.fields()
                          if getattr(self, '%s__exists' % f))

    def _get_startIndex(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, TYPE_Coordinate, 'startIndex')
            self._cache[1] = r
        return r

    def _establish_parentage_startIndex(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_startIndex), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_startIndex
                v._pbf_establish_parent_callback = self._establish_parentage_startIndex

    def _set_startIndex(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_startIndex(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field startIndex"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = TYPE_Coordinate

    def _mod_startIndex(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = TYPE_Coordinate

    def _del_startIndex(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "startIndex"

    startIndex = property(_get_startIndex, _set_startIndex, _del_startIndex)

    @property
    def startIndex__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def startIndex__type(self):
        return TYPE_Coordinate

    def _finalize_startIndex(cls):
        if is_string(TYPE_Coordinate):
            cls._pbf_strings.append(1)
        elif _PB_type(TYPE_Coordinate) is _PB_type:
            assert issubclass(TYPE_Coordinate, RepeatedSequence)
            if is_string(TYPE_Coordinate.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_startIndex)


    def _get_boundary(self):
        if 2 in self._cache:
            r = self._cache[2]
        else:
            r = self._buf_get(2, TYPE_Coordinate, 'boundary')
            self._cache[2] = r
        return r

    def _establish_parentage_boundary(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_boundary), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_boundary
                v._pbf_establish_parent_callback = self._establish_parentage_boundary

    def _set_boundary(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_boundary(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field boundary"
            raise ProtoValueError(list_assign_error)
        self._cache[2] = v
        self._mods[2] = TYPE_Coordinate

    def _mod_boundary(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[2] = TYPE_Coordinate

    def _del_boundary(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 2 in self._cache:
            del self._cache[2]
        if 2 in self._mods:
            del self._mods[2]
        self._buf_del(2)

    _pb_field_name_2 = "boundary"

    boundary = property(_get_boundary, _set_boundary, _del_boundary)

    @property
    def boundary__exists(self):
        return 2 in self._mods or self._buf_exists(2)

    @property
    def boundary__type(self):
        return TYPE_Coordinate

    def _finalize_boundary(cls):
        if is_string(TYPE_Coordinate):
            cls._pbf_strings.append(2)
        elif _PB_type(TYPE_Coordinate) is _PB_type:
            assert issubclass(TYPE_Coordinate, RepeatedSequence)
            if is_string(TYPE_Coordinate.pb_subtype):
                cls._pbf_strings.append(2)

    _pbf_finalizers.append(_finalize_boundary)


    class Repeated_cell(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Cell
        pb_subtype = pb_subtype()


    TYPE_Repeated_cell = Repeated_cell


    @property
    def cell__stream(self):
        if 3 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[3]]
        return self._get_repeated(3, self.TYPE_Repeated_cell, "cell", lazy=True)

    def cell__fast_append(self, value):
        self._append_to_repeated(3, self.TYPE_Repeated_cell, value)

    def _get_cell(self):
        if 3 in self._cache:
            r = self._cache[3]
        else:
            r = self._buf_get(3, self.TYPE_Repeated_cell, 'cell')
            self._cache[3] = r
        return r

    def _establish_parentage_cell(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_cell), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_cell
                v._pbf_establish_parent_callback = self._establish_parentage_cell

    def _set_cell(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_cell(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field cell"
            raise ProtoValueError(list_assign_error)
        self._cache[3] = v
        self._mods[3] = self.TYPE_Repeated_cell

    def _mod_cell(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[3] = self.TYPE_Repeated_cell

    def _del_cell(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 3 in self._cache:
            del self._cache[3]
        if 3 in self._mods:
            del self._mods[3]
        self._buf_del(3)

    _pb_field_name_3 = "cell"

    cell = property(_get_cell, _set_cell, _del_cell)

    @property
    def cell__exists(self):
        return 3 in self._mods or self._buf_exists(3)

    @property
    def cell__type(self):
        return self.TYPE_Repeated_cell

    def _finalize_cell(cls):
        if is_string(cls.TYPE_Repeated_cell):
            cls._pbf_strings.append(3)
        elif _PB_type(cls.TYPE_Repeated_cell) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_cell, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_cell.pb_subtype):
                cls._pbf_strings.append(3)

    _pbf_finalizers.append(_finalize_cell)


TYPE_Map = Map
_PB_finalizers.append('Map')


for cname in _PB_finalizers:
    eval(cname)._pbf_finalize()

del _PB_finalizers

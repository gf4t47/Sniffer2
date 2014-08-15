from palm.palm import ProtoBase, is_string, RepeatedSequence, ProtoValueError

_PB_type = type
_PB_finalizers = []

import cell_palm

class Leak(ProtoBase):
    _required = [1, 2]
    _field_map = {'concentration': 2, 'location': 1}
    
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
        return ['location', 'concentration']

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

    def _get_location(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, TYPE_Coordinate, 'location')
            self._cache[1] = r
        return r

    def _establish_parentage_location(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_location), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_location
                v._pbf_establish_parent_callback = self._establish_parentage_location

    def _set_location(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_location(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field location"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = TYPE_Coordinate

    def _mod_location(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = TYPE_Coordinate

    def _del_location(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "location"

    location = property(_get_location, _set_location, _del_location)

    @property
    def location__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def location__type(self):
        return TYPE_Coordinate

    def _finalize_location(cls):
        if is_string(TYPE_Coordinate):
            cls._pbf_strings.append(1)
        elif _PB_type(TYPE_Coordinate) is _PB_type:
            assert issubclass(TYPE_Coordinate, RepeatedSequence)
            if is_string(TYPE_Coordinate.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_location)


    def _get_concentration(self):
        if 2 in self._cache:
            r = self._cache[2]
        else:
            r = self._buf_get(2, ProtoBase.TYPE_double, 'concentration')
            self._cache[2] = r
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
        self._cache[2] = v
        self._mods[2] = ProtoBase.TYPE_double

    def _mod_concentration(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[2] = ProtoBase.TYPE_double

    def _del_concentration(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 2 in self._cache:
            del self._cache[2]
        if 2 in self._mods:
            del self._mods[2]
        self._buf_del(2)

    _pb_field_name_2 = "concentration"

    concentration = property(_get_concentration, _set_concentration, _del_concentration)

    @property
    def concentration__exists(self):
        return 2 in self._mods or self._buf_exists(2)

    @property
    def concentration__type(self):
        return ProtoBase.TYPE_double

    def _finalize_concentration(cls):
        if is_string(ProtoBase.TYPE_double):
            cls._pbf_strings.append(2)
        elif _PB_type(ProtoBase.TYPE_double) is _PB_type:
            assert issubclass(ProtoBase.TYPE_double, RepeatedSequence)
            if is_string(ProtoBase.TYPE_double.pb_subtype):
                cls._pbf_strings.append(2)

    _pbf_finalizers.append(_finalize_concentration)


TYPE_Leak = Leak
_PB_finalizers.append('Leak')

class Hypothesis(ProtoBase):
    _required = [1]
    _field_map = {'leak': 2, 'probability': 1, 'methene_cells': 3}
    
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
        return ['probability', 'leak', 'methene_cells']

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

    def _get_probability(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, ProtoBase.TYPE_double, 'probability')
            self._cache[1] = r
        return r

    def _establish_parentage_probability(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_probability), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_probability
                v._pbf_establish_parent_callback = self._establish_parentage_probability

    def _set_probability(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_probability(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field probability"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = ProtoBase.TYPE_double

    def _mod_probability(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = ProtoBase.TYPE_double

    def _del_probability(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "probability"

    probability = property(_get_probability, _set_probability, _del_probability)

    @property
    def probability__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def probability__type(self):
        return ProtoBase.TYPE_double

    def _finalize_probability(cls):
        if is_string(ProtoBase.TYPE_double):
            cls._pbf_strings.append(1)
        elif _PB_type(ProtoBase.TYPE_double) is _PB_type:
            assert issubclass(ProtoBase.TYPE_double, RepeatedSequence)
            if is_string(ProtoBase.TYPE_double.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_probability)


    class Repeated_leak(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Leak
        pb_subtype = pb_subtype()


    TYPE_Repeated_leak = Repeated_leak


    @property
    def leak__stream(self):
        if 2 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[2]]
        return self._get_repeated(2, self.TYPE_Repeated_leak, "leak", lazy=True)

    def leak__fast_append(self, value):
        self._append_to_repeated(2, self.TYPE_Repeated_leak, value)

    def _get_leak(self):
        if 2 in self._cache:
            r = self._cache[2]
        else:
            r = self._buf_get(2, self.TYPE_Repeated_leak, 'leak')
            self._cache[2] = r
        return r

    def _establish_parentage_leak(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_leak), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_leak
                v._pbf_establish_parent_callback = self._establish_parentage_leak

    def _set_leak(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_leak(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field leak"
            raise ProtoValueError(list_assign_error)
        self._cache[2] = v
        self._mods[2] = self.TYPE_Repeated_leak

    def _mod_leak(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[2] = self.TYPE_Repeated_leak

    def _del_leak(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 2 in self._cache:
            del self._cache[2]
        if 2 in self._mods:
            del self._mods[2]
        self._buf_del(2)

    _pb_field_name_2 = "leak"

    leak = property(_get_leak, _set_leak, _del_leak)

    @property
    def leak__exists(self):
        return 2 in self._mods or self._buf_exists(2)

    @property
    def leak__type(self):
        return self.TYPE_Repeated_leak

    def _finalize_leak(cls):
        if is_string(cls.TYPE_Repeated_leak):
            cls._pbf_strings.append(2)
        elif _PB_type(cls.TYPE_Repeated_leak) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_leak, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_leak.pb_subtype):
                cls._pbf_strings.append(2)

    _pbf_finalizers.append(_finalize_leak)


    class Repeated_methene_cells(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Cells
        pb_subtype = pb_subtype()


    TYPE_Repeated_methene_cells = Repeated_methene_cells


    @property
    def methene_cells__stream(self):
        if 3 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[3]]
        return self._get_repeated(3, self.TYPE_Repeated_methene_cells, "methene_cells", lazy=True)

    def methene_cells__fast_append(self, value):
        self._append_to_repeated(3, self.TYPE_Repeated_methene_cells, value)

    def _get_methene_cells(self):
        if 3 in self._cache:
            r = self._cache[3]
        else:
            r = self._buf_get(3, self.TYPE_Repeated_methene_cells, 'methene_cells')
            self._cache[3] = r
        return r

    def _establish_parentage_methene_cells(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_methene_cells), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_methene_cells
                v._pbf_establish_parent_callback = self._establish_parentage_methene_cells

    def _set_methene_cells(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_methene_cells(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field methene_cells"
            raise ProtoValueError(list_assign_error)
        self._cache[3] = v
        self._mods[3] = self.TYPE_Repeated_methene_cells

    def _mod_methene_cells(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[3] = self.TYPE_Repeated_methene_cells

    def _del_methene_cells(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 3 in self._cache:
            del self._cache[3]
        if 3 in self._mods:
            del self._mods[3]
        self._buf_del(3)

    _pb_field_name_3 = "methene_cells"

    methene_cells = property(_get_methene_cells, _set_methene_cells, _del_methene_cells)

    @property
    def methene_cells__exists(self):
        return 3 in self._mods or self._buf_exists(3)

    @property
    def methene_cells__type(self):
        return self.TYPE_Repeated_methene_cells

    def _finalize_methene_cells(cls):
        if is_string(cls.TYPE_Repeated_methene_cells):
            cls._pbf_strings.append(3)
        elif _PB_type(cls.TYPE_Repeated_methene_cells) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_methene_cells, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_methene_cells.pb_subtype):
                cls._pbf_strings.append(3)

    _pbf_finalizers.append(_finalize_methene_cells)


TYPE_Hypothesis = Hypothesis
_PB_finalizers.append('Hypothesis')

class Hypotheses(ProtoBase):
    _required = []
    _field_map = {'hyp': 1}
    
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
        return ['hyp']

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

    class Repeated_hyp(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Hypothesis
        pb_subtype = pb_subtype()


    TYPE_Repeated_hyp = Repeated_hyp


    @property
    def hyp__stream(self):
        if 1 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[1]]
        return self._get_repeated(1, self.TYPE_Repeated_hyp, "hyp", lazy=True)

    def hyp__fast_append(self, value):
        self._append_to_repeated(1, self.TYPE_Repeated_hyp, value)

    def _get_hyp(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, self.TYPE_Repeated_hyp, 'hyp')
            self._cache[1] = r
        return r

    def _establish_parentage_hyp(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_hyp), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_hyp
                v._pbf_establish_parent_callback = self._establish_parentage_hyp

    def _set_hyp(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_hyp(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field hyp"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = self.TYPE_Repeated_hyp

    def _mod_hyp(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = self.TYPE_Repeated_hyp

    def _del_hyp(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "hyp"

    hyp = property(_get_hyp, _set_hyp, _del_hyp)

    @property
    def hyp__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def hyp__type(self):
        return self.TYPE_Repeated_hyp

    def _finalize_hyp(cls):
        if is_string(cls.TYPE_Repeated_hyp):
            cls._pbf_strings.append(1)
        elif _PB_type(cls.TYPE_Repeated_hyp) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_hyp, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_hyp.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_hyp)


TYPE_Hypotheses = Hypotheses
_PB_finalizers.append('Hypotheses')

class Hypotheses_history(ProtoBase):
    _required = []
    _field_map = {'hyps': 1}
    
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
        return ['hyps']

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

    class Repeated_hyps(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Hypotheses
        pb_subtype = pb_subtype()


    TYPE_Repeated_hyps = Repeated_hyps


    @property
    def hyps__stream(self):
        if 1 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[1]]
        return self._get_repeated(1, self.TYPE_Repeated_hyps, "hyps", lazy=True)

    def hyps__fast_append(self, value):
        self._append_to_repeated(1, self.TYPE_Repeated_hyps, value)

    def _get_hyps(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, self.TYPE_Repeated_hyps, 'hyps')
            self._cache[1] = r
        return r

    def _establish_parentage_hyps(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_hyps), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_hyps
                v._pbf_establish_parent_callback = self._establish_parentage_hyps

    def _set_hyps(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_hyps(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field hyps"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = self.TYPE_Repeated_hyps

    def _mod_hyps(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = self.TYPE_Repeated_hyps

    def _del_hyps(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "hyps"

    hyps = property(_get_hyps, _set_hyps, _del_hyps)

    @property
    def hyps__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def hyps__type(self):
        return self.TYPE_Repeated_hyps

    def _finalize_hyps(cls):
        if is_string(cls.TYPE_Repeated_hyps):
            cls._pbf_strings.append(1)
        elif _PB_type(cls.TYPE_Repeated_hyps) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_hyps, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_hyps.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_hyps)


TYPE_Hypotheses_history = Hypotheses_history
_PB_finalizers.append('Hypotheses_history')


for cname in _PB_finalizers:
    eval(cname)._pbf_finalize()

del _PB_finalizers

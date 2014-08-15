from palm.palm import ProtoBase, is_string, RepeatedSequence, ProtoValueError

_PB_type = type
_PB_finalizers = []

import hypothesis_palm

class Detection(ProtoBase):
    _required = [1]
    _field_map = {'leak': 2, 'time': 1}
    
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
        return ['time', 'leak']

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

    def _get_time(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, ProtoBase.TYPE_int32, 'time')
            self._cache[1] = r
        return r

    def _establish_parentage_time(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_time), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_time
                v._pbf_establish_parent_callback = self._establish_parentage_time

    def _set_time(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_time(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field time"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = ProtoBase.TYPE_int32

    def _mod_time(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = ProtoBase.TYPE_int32

    def _del_time(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "time"

    time = property(_get_time, _set_time, _del_time)

    @property
    def time__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def time__type(self):
        return ProtoBase.TYPE_int32

    def _finalize_time(cls):
        if is_string(ProtoBase.TYPE_int32):
            cls._pbf_strings.append(1)
        elif _PB_type(ProtoBase.TYPE_int32) is _PB_type:
            assert issubclass(ProtoBase.TYPE_int32, RepeatedSequence)
            if is_string(ProtoBase.TYPE_int32.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_time)


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


TYPE_Detection = Detection
_PB_finalizers.append('Detection')

class Detections(ProtoBase):
    _required = []
    _field_map = {'dect': 1}
    
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
        return ['dect']

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

    class Repeated_dect(RepeatedSequence):
        class pb_subtype(object):
            def __get__(self, instance, cls):
                return TYPE_Detection
        pb_subtype = pb_subtype()


    TYPE_Repeated_dect = Repeated_dect


    @property
    def dect__stream(self):
        if 1 in self._cache:
            def acc(v):
                v_ = lambda: v
                return v_
            return [acc(v) for v in self._cache[1]]
        return self._get_repeated(1, self.TYPE_Repeated_dect, "dect", lazy=True)

    def dect__fast_append(self, value):
        self._append_to_repeated(1, self.TYPE_Repeated_dect, value)

    def _get_dect(self):
        if 1 in self._cache:
            r = self._cache[1]
        else:
            r = self._buf_get(1, self.TYPE_Repeated_dect, 'dect')
            self._cache[1] = r
        return r

    def _establish_parentage_dect(self, v):
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            if v._pbf_parent_callback:
                assert (v._pbf_parent_callback == self._mod_dect), "subobjects can only have one parent--use copy()?"
            else:
                v._pbf_parent_callback = self._mod_dect
                v._pbf_establish_parent_callback = self._establish_parentage_dect

    def _set_dect(self, v, modifying=True):
        self._evermod = modifying or self._evermod
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if isinstance(v, (ProtoBase, RepeatedSequence)):
            self._establish_parentage_dect(v)
        elif isinstance(v, list):
            list_assign_error = "Can't assign list to repeated field dect"
            raise ProtoValueError(list_assign_error)
        self._cache[1] = v
        self._mods[1] = self.TYPE_Repeated_dect

    def _mod_dect(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        self._mods[1] = self.TYPE_Repeated_dect

    def _del_dect(self):
        self._evermod = True
        if self._pbf_parent_callback:
            self._pbf_parent_callback()
        if 1 in self._cache:
            del self._cache[1]
        if 1 in self._mods:
            del self._mods[1]
        self._buf_del(1)

    _pb_field_name_1 = "dect"

    dect = property(_get_dect, _set_dect, _del_dect)

    @property
    def dect__exists(self):
        return 1 in self._mods or self._buf_exists(1)

    @property
    def dect__type(self):
        return self.TYPE_Repeated_dect

    def _finalize_dect(cls):
        if is_string(cls.TYPE_Repeated_dect):
            cls._pbf_strings.append(1)
        elif _PB_type(cls.TYPE_Repeated_dect) is _PB_type:
            assert issubclass(cls.TYPE_Repeated_dect, RepeatedSequence)
            if is_string(cls.TYPE_Repeated_dect.pb_subtype):
                cls._pbf_strings.append(1)

    _pbf_finalizers.append(_finalize_dect)


TYPE_Detections = Detections
_PB_finalizers.append('Detections')


for cname in _PB_finalizers:
    eval(cname)._pbf_finalize()

del _PB_finalizers

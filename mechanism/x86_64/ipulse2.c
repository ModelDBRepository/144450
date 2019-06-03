/* Created by Language version: 6.0.2 */
/* NOT VECTORIZED */
#include <stdio.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 
#include "md1redef.h"
#include "section.h"
#include "nrnoc_ml.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#undef exp
#define exp hoc_Exp
extern double hoc_Exp();
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define delta_t dt
#define del _p[0]
#define dur _p[1]
#define per _p[2]
#define num _p[3]
#define amp _p[4]
#define i _p[5]
#define ival _p[6]
#define on _p[7]
#define tally _p[8]
#define _g _p[9]
#define _tsav _p[10]
#define _nd_area  *_ppvar[0].pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 /* external NEURON variables */
 extern double dt;
 extern double t;
 /* declaration of user functions */
 static int _mechtype;
extern int nrn_get_mechtype();
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 static _hoc_setdata(_vptr) void* _vptr; { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 0,0
};
 static struct Member_func {
	char* _name; double (*_member)();} _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "dur", 0, 1e+09,
 "per", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "del", "ms",
 "dur", "ms",
 "per", "ms",
 "amp", "nA",
 "i", "nA",
 0,0
};
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static nrn_alloc(), nrn_init(), nrn_state();
 static nrn_cur(), nrn_jacob();
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.0.2",
"Ipulse2",
 "del",
 "dur",
 "per",
 "num",
 "amp",
 0,
 "i",
 0,
 0,
 0};
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 11);
 	/*initialize range parameters*/
 	del = 0;
 	dur = 0;
 	per = 0;
 	num = 0;
 	amp = 0;
  }
 	_prop->param = _p;
 	_prop->param_size = 11;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static _initlists();
 
#define _tqitem &(_ppvar[2]._pvoid)
 static _net_receive();
 typedef (*_Pfrv)();
 extern _Pfrv* pnt_receive;
 extern short* pnt_receive_size;
 _ipulse2_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func,
	 _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 3);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 Ipulse2 /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/ipulse2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
 
static _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{ _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 1.0 ) {
     if ( on  == 0.0 ) {
       ival = amp ;
       on = 1.0 ;
       net_send ( _tqitem, _args, _pnt, dur , 1.0 ) ;
       }
     else {
       ival = 0.0 ;
       on = 0.0 ;
       if ( tally > 0.0 ) {
         net_send ( _tqitem, _args, _pnt, per - dur , 1.0 ) ;
         tally = tally - 1.0 ;
         }
       }
     }
   } }

static initmodel() {
  int _i; double _save;_ninits++;
{
 {
   if ( dur >= per ) {
     per = dur + 1.0 ;
     printf ( "per must be longer than dur\n" ) ;
      printf ( "per has been increased to %g ms\n" , per ) ;
      }
   i = 0.0 ;
   ival = 0.0 ;
   tally = num ;
   if ( tally > 0.0 ) {
     net_send ( _tqitem, (double*)0, _ppvar[1]._pvoid, del , 1.0 ) ;
     on = 0.0 ;
     tally = tally - 1.0 ;
     }
   }

}
}

static nrn_init(_ml, _type) _Memb_list* _ml; int _type;{
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 }
 v = _v;
 initmodel();
}}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   i = ival ;
   }
 _current += i;

} return _current;
}

static nrn_cur(_ml, _type) _Memb_list* _ml; int _type;{
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if EXTRACELLULAR
 _nd = _ml->_nodelist[_iml];
 if (_nd->_extnode) {
    _v = NODEV(_nd) +_nd->_extnode->_v[0];
 }else
#endif
 {
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 }
 _g = _nrn_current(_v + .001);
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) += _rhs;
  }else
#endif
  {
	NODERHS(_nd) += _rhs;
  }
#if EXTRACELLULAR
 if (_nd->_extnode) {
   *_nd->_extnode->_rhs[0] += _rhs;
 }
#endif
 
}}

static nrn_jacob(_ml, _type) _Memb_list* _ml; int _type;{
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) -= _g;
  }else
#endif
  {
	NODED(_nd) -= _g;
  }
#if EXTRACELLULAR
 if (_nd->_extnode) {
   *_nd->_extnode->_d[0] += _g;
 }
#endif
 
}}

static nrn_state(_ml, _type) _Memb_list* _ml; int _type;{

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
_first = 0;
}

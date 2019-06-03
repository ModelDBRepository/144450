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
#define K _p[0]
#define gbar _p[1]
#define vhalf _p[2]
#define ihi _p[3]
#define ninf _p[4]
#define taun _p[5]
#define g _p[6]
#define n _p[7]
#define ehi _p[8]
#define Dn _p[9]
#define _g _p[10]
#define _ion_ehi	*_ppvar[0].pval
#define _ion_ihi	*_ppvar[1].pval
#define _ion_dihidv	*_ppvar[2].pval
 
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
 static int _hoc_rates();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("h");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_h", _hoc_setdata,
 "rates_h", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
#define ena ena_h
 double ena = 50;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ena_h", "mV",
 "K_h", "mV",
 "gbar_h", "mho/cm2",
 "vhalf_h", "mV",
 "ihi_h", "mA/cm2",
 "taun_h", "ms",
 0,0
};
 static double n0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ena_h", &ena,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static nrn_alloc(), nrn_init(), nrn_state();
 static nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
extern int nrn_cvode_;
 
#define _cvode_ieq _ppvar[3]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.0.2",
"h",
 "K_h",
 "gbar_h",
 "vhalf_h",
 0,
 "ihi_h",
 "ninf_h",
 "taun_h",
 "g_h",
 0,
 "n_h",
 0,
 0};
 static Symbol* _hi_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 11);
 	/*initialize range parameters*/
 	K = 8.5;
 	gbar = 0;
 	vhalf = -90;
 	_prop->param = _p;
 	_prop->param_size = 11;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_hi_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0].pval = &prop_ion->param[0]; /* ehi */
 	_ppvar[1].pval = &prop_ion->param[3]; /* ihi */
 	_ppvar[2].pval = &prop_ion->param[4]; /* _ion_dihidv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _h_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("hi", 1.0);
 	_hi_sym = hoc_lookup("hi_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 4);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 h /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/h.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "H-current that uses Na ions";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[1], _dlist1[1];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates (  ) ;
   Dn = ( ninf - n ) / taun ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 rates (  ) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / taun )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates (  ) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / taun)))*(- ( ( ( ninf ) ) / taun ) / ( ( ( ( - 1.0) ) ) / taun ) - n) ;
   }
  return 0;
}
 
static int  rates (  )  {
   if ( v > - 30.0 ) {
     taun = 1.0 ;
     }
   else {
     taun = 2.0 * ( 1.0 / ( exp ( ( v + 145.0 ) / - 17.5 ) + exp ( ( v + 16.8 ) / 16.5 ) ) + 5.0 ) ;
     }
   ninf = 1.0 - ( 1.0 / ( 1.0 + exp ( ( vhalf - v ) / K ) ) ) ;
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 1;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  ehi = _ion_ehi;
  _ode_spec1();
  }
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; {
	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  ehi = _ion_ehi;
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  n = n0;
 {
   rates (  ) ;
   n = ninf ;
   g = gbar * n ;
   ihi = g * ( v - ehi ) ;
   }
  _sav_indep = t; t = _save;

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
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  ehi = _ion_ehi;
 initmodel();
 }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   g = gbar * n ;
   ihi = g * ( v - ehi ) ;
   }
 _current += ihi;

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
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  ehi = _ion_ehi;
 _g = _nrn_current(_v + .001);
 	{ static double _dihi;
  _dihi = ihi;
 _rhs = _nrn_current(_v);
  _ion_dihidv += (_dihi - ihi)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ihi += ihi ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static nrn_jacob(_ml, _type) _Memb_list* _ml; int _type;{
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static nrn_state(_ml, _type) _Memb_list* _ml; int _type;{
 double _break, _save;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _break = t + .5*dt; _save = t; delta_t = dt;
 v=_v;
{
  ehi = _ion_ehi;
 { {
 for (; t < _break; t += delta_t) {
 error =  states();
 if(error){fprintf(stderr,"at line 62 in file h.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(n) - _p;  _dlist1[0] = &(Dn) - _p;
_first = 0;
}

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
#define gcalbar _p[0]
#define ica _p[1]
#define po _p[2]
#define m _p[3]
#define s _p[4]
#define cai _p[5]
#define eca _p[6]
#define Dm _p[7]
#define Ds _p[8]
#define _g _p[9]
#define _ion_cai	*_ppvar[0].pval
#define _ion_eca	*_ppvar[1].pval
#define _ion_ica	*_ppvar[2].pval
#define _ion_dicadv	*_ppvar[3].pval
 
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
 extern double celsius;
 extern double dt;
 extern double t;
 /* declaration of user functions */
 static int _hoc_alp();
 static int _hoc_h2();
 static int _hoc_rates();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("cal");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_cal", _hoc_setdata,
 "alp_cal", _hoc_alp,
 "h2_cal", _hoc_h2,
 "rates_cal", _hoc_rates,
 0, 0
};
#define alp alp_cal
#define h2 h2_cal
 extern double alp();
 extern double h2();
 /* declare global and static user variables */
#define bo bo_cal
 double bo = 8;
#define ba ba_cal
 double ba = 0.01;
#define b b_cal
 double b = 0.01;
#define inf inf_cal
 double inf = 0;
#define ki ki_cal
 double ki = 0.025;
#define s_inf s_inf_cal
 double s_inf = 0;
#define t0 t0_cal
 double t0 = 1.5;
#define taumin taumin_cal
 double taumin = 180;
#define tau_m tau_m_cal
 double tau_m = 0;
#define vhalf vhalf_cal
 double vhalf = -1;
#define zeta zeta_cal
 double zeta = -4.6;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "ki_cal", "mM",
 "taumin_cal", "ms",
 "vhalf_cal", "mV",
 "t0_cal", "ms",
 "b_cal", "mM",
 "ba_cal", "mM",
 "tau_m_cal", "ms",
 "gcalbar_cal", "mho/cm2",
 "ica_cal", "mA/cm2",
 0,0
};
 static double m0 = 0;
 static double s0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "ki_cal", &ki,
 "taumin_cal", &taumin,
 "vhalf_cal", &vhalf,
 "zeta_cal", &zeta,
 "t0_cal", &t0,
 "b_cal", &b,
 "ba_cal", &ba,
 "bo_cal", &bo,
 "inf_cal", &inf,
 "s_inf_cal", &s_inf,
 "tau_m_cal", &tau_m,
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
 
#define _cvode_ieq _ppvar[4]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.0.2",
"cal",
 "gcalbar_cal",
 0,
 "ica_cal",
 "po_cal",
 0,
 "m_cal",
 "s_cal",
 0,
 0};
 static Symbol* _ca_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 10);
 	/*initialize range parameters*/
 	gcalbar = 0;
 	_prop->param = _p;
 	_prop->param_size = 10;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0].pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1].pval = &prop_ion->param[0]; /* eca */
 	_ppvar[2].pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3].pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _cal_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 5);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cal /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/cal.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.31342;
static int _reset;
static char *modelname = "L-type calcium channel with high threshold for activation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[2], _dlist1[2];
 static int states();
 
double h2 (  _lcai )  
	double _lcai ;
 {
   double _lh2;
 _lh2 = ki / ( ki + _lcai ) ;
   
return _lh2;
 }
 static int _hoc_h2() {
 double _r;
 _r =  h2 (  *getarg(1) ) ;
 ret(_r);
}
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates (  v , cai ) ;
   Dm = ( inf - m ) / t0 ;
   Ds = ( s_inf - s ) / tau_m ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 rates (  v , cai ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / t0 )) ;
 Ds = Ds  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_m )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates (  v , cai ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / t0)))*(- ( ( ( inf ) ) / t0 ) / ( ( ( ( - 1.0) ) ) / t0 ) - m) ;
    s = s + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau_m)))*(- ( ( ( s_inf ) ) / tau_m ) / ( ( ( ( - 1.0) ) ) / tau_m ) - s) ;
   }
  return 0;
}
 
double alp (  _lv )  
	double _lv ;
 {
   double _lalp;
  _lalp = exp ( 1.e-3 * zeta * ( _lv - vhalf ) * 9.648e4 / ( 8.315 * ( 273.16 + celsius ) ) ) ;
    
return _lalp;
 }
 static int _hoc_alp() {
 double _r;
 _r =  alp (  *getarg(1) ) ;
 ret(_r);
}
 
static int  rates (  _lv , _lcai )  
	double _lv , _lcai ;
 {
   double _la , _lalpha2 ;
 _la = alp (  _lv ) ;
   inf = 1.0 / ( 1.0 + _la ) ;
   _lalpha2 = pow( ( _lcai / b ) , 2.0 ) ;
   s_inf = _lalpha2 / ( _lalpha2 + 1.0 ) ;
   tau_m = taumin + 1.0 * 1.0 / ( _lcai + ba ) ;
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 2;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  cai = _ion_cai;
  eca = _ion_eca;
  _ode_spec1();
  }
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; {
	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  cai = _ion_cai;
  eca = _ion_eca;
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  m = m0;
  s = s0;
 {
   rates (  v , cai ) ;
   m = inf ;
   s = s_inf ;
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
  cai = _ion_cai;
  eca = _ion_eca;
 initmodel();
 }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   po = m * m * h2 (  cai ) ;
   ica = gcalbar * ( po + s * s * bo ) * ( v - eca ) ;
   }
 _current += ica;

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
  cai = _ion_cai;
  eca = _ion_eca;
 _g = _nrn_current(_v + .001);
 	{ static double _dica;
  _dica = ica;
 _rhs = _nrn_current(_v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
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
  cai = _ion_cai;
  eca = _ion_eca;
 { {
 for (; t < _break; t += delta_t) {
 error =  states();
 if(error){fprintf(stderr,"at line 68 in file cal.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
 _slist1[1] = &(s) - _p;  _dlist1[1] = &(Ds) - _p;
_first = 0;
}

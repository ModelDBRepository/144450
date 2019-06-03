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
#define gcabar _p[0]
#define ica _p[1]
#define inf (_p + 2)
#define tau (_p + 4)
#define m _p[6]
#define h _p[7]
#define ecar _p[8]
#define cai _p[9]
#define cao _p[10]
#define Dm _p[11]
#define Dh _p[12]
#define _g _p[13]
#define _ion_cai	*_ppvar[0].pval
#define _ion_cao	*_ppvar[1].pval
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
 static int _hoc_rates();
 static int _hoc_varss();
 static int _hoc_vartau();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("car");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_car", _hoc_setdata,
 "rates_car", _hoc_rates,
 "varss_car", _hoc_varss,
 "vartau_car", _hoc_vartau,
 0, 0
};
#define varss varss_car
#define vartau vartau_car
 extern double varss();
 extern double vartau();
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gcabar_car", "mho/cm2",
 "ica_car", "mA/cm2",
 "tau_car", "ms",
 0,0
};
 static double h0 = 0;
 static double m0 = 0;
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
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
extern int nrn_cvode_;
 
#define _cvode_ieq _ppvar[4]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.0.2",
"car",
 "gcabar_car",
 0,
 "ica_car",
 "inf_car[2]",
 "tau_car[2]",
 0,
 "m_car",
 "h_car",
 0,
 0};
 static Symbol* _ca_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14);
 	/*initialize range parameters*/
 	gcabar = 0;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0].pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1].pval = &prop_ion->param[2]; /* cao */
 	_ppvar[2].pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3].pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _car_reg() {
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
 	ivoc_help("help ?1 car /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/car.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.31342;
static int _reset;
static char *modelname = "Ca R-type channel with medium threshold for activation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[2], _dlist1[2];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates (  v ) ;
   Dm = ( inf [ 0 ] - m ) / tau [ 0 ] ;
   Dh = ( inf [ 1 ] - h ) / tau [ 1 ] ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 rates (  v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau[0] )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau[1] )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates (  v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau[0])))*(- ( ( ( inf[0] ) ) / tau[0] ) / ( ( ( ( - 1.0) ) ) / tau[0] ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau[1])))*(- ( ( ( inf[1] ) ) / tau[1] ) / ( ( ( ( - 1.0) ) ) / tau[1] ) - h) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   double _la , _lb ;
 {int  _li ;for ( _li = 0 ; _li <= 1 ; _li ++ ) {
     tau [ _li ] = vartau (  _lv , ((double) _li ) ) ;
     inf [ _li ] = varss (  _lv , ((double) _li ) ) ;
     } }
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  *getarg(1) ) ;
 ret(_r);
}
 
double varss (  _lv , _li )  
	double _lv , _li ;
 {
   double _lvarss;
 if ( _li  == 0.0 ) {
     _lvarss = 1.0 / ( 1.0 + exp ( ( _lv + 48.5 ) / ( - 3.0 ) ) ) ;
     }
   else if ( _li  == 1.0 ) {
     _lvarss = 1.0 / ( 1.0 + exp ( ( _lv + 53.0 ) / ( 1.0 ) ) ) ;
     }
   
return _lvarss;
 }
 static int _hoc_varss() {
 double _r;
 _r =  varss (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
double vartau (  _lv , _li )  
	double _lv , _li ;
 {
   double _lvartau;
 if ( _li  == 0.0 ) {
     _lvartau = 120.0 ;
     }
   else if ( _li  == 1.0 ) {
     _lvartau = 4.0 ;
     }
   
return _lvartau;
 }
 static int _hoc_vartau() {
 double _r;
 _r =  vartau (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 2;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  cai = _ion_cai;
  cao = _ion_cao;
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
  cao = _ion_cao;
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
 {
   rates (  v ) ;
   m = 0.0 ;
   h = 1.0 ;
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
  cao = _ion_cao;
 initmodel();
 }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   ecar = ( 1e3 ) * ( R * ( celsius + 273.15 ) ) / ( 2.0 * FARADAY ) * log ( cao / cai ) ;
   ica = gcabar * m * m * m * h * ( v - ecar ) ;
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
  cao = _ion_cao;
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
  cao = _ion_cao;
 { {
 for (; t < _break; t += delta_t) {
 error =  states();
 if(error){fprintf(stderr,"at line 58 in file car.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
_first = 0;
}

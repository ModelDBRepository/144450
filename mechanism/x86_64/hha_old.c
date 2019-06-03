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
#define ar2 _p[0]
#define W _p[1]
#define gnabar _p[2]
#define gkbar _p[3]
#define gl _p[4]
#define el _p[5]
#define il _p[6]
#define m _p[7]
#define h _p[8]
#define n _p[9]
#define s _p[10]
#define Dm _p[11]
#define Dh _p[12]
#define Dn _p[13]
#define Ds _p[14]
#define ena _p[15]
#define ek _p[16]
#define ina _p[17]
#define ik _p[18]
#define _g _p[19]
#define _ion_ena	*_ppvar[0].pval
#define _ion_ina	*_ppvar[1].pval
#define _ion_dinadv	*_ppvar[2].pval
#define _ion_ek	*_ppvar[3].pval
#define _ion_ik	*_ppvar[4].pval
#define _ion_dikdv	*_ppvar[5].pval
 
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
 static int _hoc_alpv();
 static int _hoc_alpr();
 static int _hoc_betr();
 static int _hoc_rates();
 static int _hoc_varss();
 static int _hoc_vartau();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("hha_old");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_hha_old", _hoc_setdata,
 "alpv_hha_old", _hoc_alpv,
 "alpr_hha_old", _hoc_alpr,
 "betr_hha_old", _hoc_betr,
 "rates_hha_old", _hoc_rates,
 "varss_hha_old", _hoc_varss,
 "vartau_hha_old", _hoc_vartau,
 0, 0
};
#define alpv alpv_hha_old
#define alpr alpr_hha_old
#define betr betr_hha_old
#define varss varss_hha_old
#define vartau vartau_hha_old
 extern double alpv();
 extern double alpr();
 extern double betr();
 extern double varss();
 extern double vartau();
 /* declare global and static user variables */
#define a0r a0r_hha_old
 double a0r = 0.0003;
#define b0r b0r_hha_old
 double b0r = 0.0003;
#define gmr gmr_hha_old
 double gmr = 0.2;
#define inf inf_hha_old
 double inf[4];
#define taumin taumin_hha_old
 double taumin = 3;
#define tau tau_hha_old
 double tau[4];
#define vvh vvh_hha_old
 double vvh = -58;
#define vhalfr vhalfr_hha_old
 double vhalfr = -60;
#define vvs vvs_hha_old
 double vvs = 2;
#define zetas zetas_hha_old
 double zetas = 12;
#define zetar zetar_hha_old
 double zetar = 12;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "a0r_hha_old", "/ms",
 "b0r_hha_old", "/ms",
 "taumin_hha_old", "ms",
 "vvs_hha_old", "mV",
 "vhalfr_hha_old", "mV",
 "vvh_hha_old", "mV",
 "tau_hha_old", "ms",
 "W_hha_old", "/mV",
 "gnabar_hha_old", "mho/cm2",
 "gkbar_hha_old", "mho/cm2",
 "gl_hha_old", "mho/cm2",
 "el_hha_old", "mV",
 "il_hha_old", "mA/cm2",
 0,0
};
 static double h0 = 0;
 static double m0 = 0;
 static double n0 = 0;
 static double s0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "a0r_hha_old", &a0r,
 "b0r_hha_old", &b0r,
 "zetar_hha_old", &zetar,
 "zetas_hha_old", &zetas,
 "gmr_hha_old", &gmr,
 "taumin_hha_old", &taumin,
 "vvs_hha_old", &vvs,
 "vhalfr_hha_old", &vhalfr,
 "vvh_hha_old", &vvh,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 "inf_hha_old", inf, 4,
 "tau_hha_old", tau, 4,
 0,0,0
};
 static double _sav_indep;
 static nrn_alloc(), nrn_init(), nrn_state();
 static nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
extern int nrn_cvode_;
 
#define _cvode_ieq _ppvar[6]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.0.2",
"hha_old",
 "ar2_hha_old",
 "W_hha_old",
 "gnabar_hha_old",
 "gkbar_hha_old",
 "gl_hha_old",
 "el_hha_old",
 0,
 "il_hha_old",
 0,
 "m_hha_old",
 "h_hha_old",
 "n_hha_old",
 "s_hha_old",
 0,
 0};
 static Symbol* _na_sym;
 static Symbol* _k_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 20);
 	/*initialize range parameters*/
 	ar2 = 1;
 	W = 0.016;
 	gnabar = 0;
 	gkbar = 0;
 	gl = 0;
 	el = -70;
 	_prop->param = _p;
 	_prop->param_size = 20;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 7);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0].pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1].pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2].pval = &prop_ion->param[4]; /* _ion_dinadv */
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[3].pval = &prop_ion->param[0]; /* ek */
 	_ppvar[4].pval = &prop_ion->param[3]; /* ik */
 	_ppvar[5].pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _hha_old_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("na", -10000.);
 	ion_reg("k", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 7);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 hha_old /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/hha_old.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "HH channel that includes both a sodium and a delayed rectifier channel ";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[4], _dlist1[4];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates (  v , ar2 ) ;
   Dm = ( inf [ 0 ] - m ) / tau [ 0 ] ;
   Dh = ( inf [ 1 ] - h ) / tau [ 1 ] ;
   Dn = ( inf [ 2 ] - n ) / tau [ 2 ] ;
   Ds = ( inf [ 3 ] - s ) / tau [ 3 ] ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 rates (  v , ar2 ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau[0] )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau[1] )) ;
 Dn = Dn  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau[2] )) ;
 Ds = Ds  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau[3] )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates (  v , ar2 ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau[0])))*(- ( ( ( inf[0] ) ) / tau[0] ) / ( ( ( ( - 1.0) ) ) / tau[0] ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau[1])))*(- ( ( ( inf[1] ) ) / tau[1] ) / ( ( ( ( - 1.0) ) ) / tau[1] ) - h) ;
    n = n + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau[2])))*(- ( ( ( inf[2] ) ) / tau[2] ) / ( ( ( ( - 1.0) ) ) / tau[2] ) - n) ;
    s = s + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tau[3])))*(- ( ( ( inf[3] ) ) / tau[3] ) / ( ( ( ( - 1.0) ) ) / tau[3] ) - s) ;
   }
  return 0;
}
 
static int  rates (  _lv , _la2 )  
	double _lv , _la2 ;
 {
   double _ltmp , _lc ;
 {int  _li ;for ( _li = 0 ; _li <= 2 ; _li ++ ) {
     tau [ _li ] = vartau (  _lv , ((double) _li ) ) ;
     inf [ _li ] = varss (  _lv , ((double) _li ) ) ;
     } }
   tau [ 3 ] = betr (  _lv ) / ( a0r * ( 1.0 + alpr (  _lv ) ) ) ;
   if ( tau [ 3 ] < taumin ) {
     tau [ 3 ] = taumin ;
     }
   _lc = alpv (  _lv ) ;
   inf [ 3 ] = _lc + _la2 * ( 1.0 - _lc ) ;
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
double varss (  _lv , _li )  
	double _lv , _li ;
 {
   double _lvarss;
 if ( _li  == 0.0 ) {
     _lvarss = 1.0 / ( 1.0 + exp ( ( _lv + 40.0 ) / ( - 3.0 ) ) ) ;
     }
   else if ( _li  == 1.0 ) {
     _lvarss = 1.0 / ( 1.0 + exp ( ( _lv + 45.0 ) / ( 3.0 ) ) ) ;
     }
   else if ( _li  == 2.0 ) {
     _lvarss = 1.0 / ( 1.0 + exp ( ( _lv + 42.0 ) / ( - 2.0 ) ) ) ;
     }
   
return _lvarss;
 }
 static int _hoc_varss() {
 double _r;
 _r =  varss (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
double alpv (  _lv )  
	double _lv ;
 {
   double _lalpv;
 _lalpv = 1.0 / ( 1.0 + exp ( ( _lv - vvh ) / vvs ) ) ;
   
return _lalpv;
 }
 static int _hoc_alpv() {
 double _r;
 _r =  alpv (  *getarg(1) ) ;
 ret(_r);
}
 
double alpr (  _lv )  
	double _lv ;
 {
   double _lalpr;
  _lalpr = exp ( 1.e-3 * zetar * ( _lv - vhalfr ) * 9.648e4 / ( 8.315 * ( 273.16 + celsius ) ) ) ;
    
return _lalpr;
 }
 static int _hoc_alpr() {
 double _r;
 _r =  alpr (  *getarg(1) ) ;
 ret(_r);
}
 
double betr (  _lv )  
	double _lv ;
 {
   double _lbetr;
  _lbetr = exp ( 1.e-3 * zetar * gmr * ( _lv - vhalfr ) * 9.648e4 / ( 8.315 * ( 273.16 + celsius ) ) ) ;
    
return _lbetr;
 }
 static int _hoc_betr() {
 double _r;
 _r =  betr (  *getarg(1) ) ;
 ret(_r);
}
 
double vartau (  _lv , _li )  
	double _lv , _li ;
 {
   double _lvartau;
 double _ltmp ;
 if ( _li  == 0.0 ) {
     _lvartau = 0.05 ;
     }
   else if ( _li  == 1.0 ) {
     _lvartau = 0.5 ;
     }
   else if ( _li  == 2.0 ) {
     _lvartau = 2.2 ;
     }
   
return _lvartau;
 }
 static int _hoc_vartau() {
 double _r;
 _r =  vartau (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 4;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  ena = _ion_ena;
  ek = _ion_ek;
  _ode_spec1();
   }
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; {
	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  ena = _ion_ena;
  ek = _ion_ek;
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  h = h0;
  m = m0;
  n = n0;
  s = s0;
 {
   rates (  v , ar2 ) ;
   m = inf [ 0 ] ;
   h = inf [ 1 ] ;
   n = inf [ 2 ] ;
   s = inf [ 3 ] ;
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
  ena = _ion_ena;
  ek = _ion_ek;
 initmodel();
  }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   ina = gnabar * m * m * h * s * ( v - ena ) ;
   ik = gkbar * n * n * ( v - ek ) ;
   il = gl * ( v - el ) ;
   }
 _current += ina;
 _current += ik;
 _current += il;

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
  ena = _ion_ena;
  ek = _ion_ek;
 _g = _nrn_current(_v + .001);
 	{ static double _dik;
 static double _dina;
  _dina = ina;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dinadv += (_dina - ina)/.001 ;
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
  _ion_ik += ik ;
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
  ena = _ion_ena;
  ek = _ion_ek;
 { {
 for (; t < _break; t += delta_t) {
 error =  states();
 if(error){fprintf(stderr,"at line 68 in file hha_old.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 }  }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
 _slist1[1] = &(h) - _p;  _dlist1[1] = &(Dh) - _p;
 _slist1[2] = &(n) - _p;  _dlist1[2] = &(Dn) - _p;
 _slist1[3] = &(s) - _p;  _dlist1[3] = &(Ds) - _p;
_first = 0;
}

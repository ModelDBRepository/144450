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
#define gcatbar _p[0]
#define iCa _p[1]
#define m _p[2]
#define h _p[3]
#define cai _p[4]
#define eca _p[5]
#define Dm _p[6]
#define Dh _p[7]
#define _g _p[8]
#define _ion_cai	*_ppvar[0].pval
#define _ion_eca	*_ppvar[1].pval
#define _ion_iCa	*_ppvar[2].pval
#define _ion_diCadv	*_ppvar[3].pval
 
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
 static int _hoc_alph();
 static int _hoc_alpm();
 static int _hoc_efun();
 static int _hoc_ghk();
 static int _hoc_rates();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("cat");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_cat", _hoc_setdata,
 "alph_cat", _hoc_alph,
 "alpm_cat", _hoc_alpm,
 "efun_cat", _hoc_efun,
 "ghk_cat", _hoc_ghk,
 "rates_cat", _hoc_rates,
 0, 0
};
#define alph alph_cat
#define alpm alpm_cat
#define efun efun_cat
#define ghk ghk_cat
 extern double alph();
 extern double alpm();
 extern double efun();
 extern double ghk();
 /* declare global and static user variables */
#define hinf hinf_cat
 double hinf = 0;
#define minf minf_cat
 double minf = 0;
#define th0 th0_cat
 double th0 = 10;
#define tm0 tm0_cat
 double tm0 = 1.5;
#define vhalfh vhalfh_cat
 double vhalfh = -68;
#define vhalfm vhalfm_cat
 double vhalfm = -36;
#define zetah zetah_cat
 double zetah = 5.2;
#define zetam zetam_cat
 double zetam = -3;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "vhalfm_cat", "mV",
 "vhalfh_cat", "mV",
 "tm0_cat", "ms",
 "th0_cat", "ms",
 "gcatbar_cat", "mho/cm2",
 "iCa_cat", "mA/cm2",
 0,0
};
 static double h0 = 0;
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "zetam_cat", &zetam,
 "zetah_cat", &zetah,
 "vhalfm_cat", &vhalfm,
 "vhalfh_cat", &vhalfh,
 "tm0_cat", &tm0,
 "th0_cat", &th0,
 "minf_cat", &minf,
 "hinf_cat", &hinf,
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
"cat",
 "gcatbar_cat",
 0,
 "iCa_cat",
 0,
 "m_cat",
 "h_cat",
 0,
 0};
 static Symbol* _ca_sym;
 static Symbol* _Ca_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 9);
 	/*initialize range parameters*/
 	gcatbar = 0;
 	_prop->param = _p;
 	_prop->param_size = 9;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 1);
 	_ppvar[0].pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1].pval = &prop_ion->param[0]; /* eca */
 prop_ion = need_memb(_Ca_sym);
 	_ppvar[2].pval = &prop_ion->param[3]; /* iCa */
 	_ppvar[3].pval = &prop_ion->param[4]; /* _ion_diCadv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _cat_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("Ca", 2.0);
 	_ca_sym = hoc_lookup("ca_ion");
 	_Ca_sym = hoc_lookup("Ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 5);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cat /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/cat.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.31342;
static int _reset;
static char *modelname = "t-type calcium channel with high threshold for activation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[2], _dlist1[2];
 static int states();
 
double ghk (  _lv , _lci , _lco )  
	double _lv , _lci , _lco ;
 {
   double _lghk;
 double _lz , _leci , _leco ;
 _lz = ( 1e-3 ) * 2.0 * FARADAY * _lv / ( R * ( celsius + 273.15 ) ) ;
   _leco = _lco * efun (  _lz ) ;
   _leci = _lci * efun (  - _lz ) ;
   _lghk = ( .001 ) * 2.0 * FARADAY * ( _leci - _leco ) ;
   
return _lghk;
 }
 static int _hoc_ghk() {
 double _r;
 _r =  ghk (  *getarg(1) , *getarg(2) , *getarg(3) ) ;
 ret(_r);
}
 
double efun (  _lz )  
	double _lz ;
 {
   double _lefun;
 if ( fabs ( _lz ) < 1e-4 ) {
     _lefun = 1.0 - _lz / 2.0 ;
     }
   else {
     _lefun = _lz / ( exp ( _lz ) - 1.0 ) ;
     }
   
return _lefun;
 }
 static int _hoc_efun() {
 double _r;
 _r =  efun (  *getarg(1) ) ;
 ret(_r);
}
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   rates (  v ) ;
   Dm = ( minf - m ) / tm0 ;
   Dh = ( hinf - h ) / th0 ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 rates (  v ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tm0 )) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / th0 )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates (  v ) ;
    m = m + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / tm0)))*(- ( ( ( minf ) ) / tm0 ) / ( ( ( ( - 1.0) ) ) / tm0 ) - m) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / th0)))*(- ( ( ( hinf ) ) / th0 ) / ( ( ( ( - 1.0) ) ) / th0 ) - h) ;
   }
  return 0;
}
 
static int  rates (  _lv )  
	double _lv ;
 {
   double _la , _lb ;
 _la = alpm (  _lv ) ;
   minf = 1.0 / ( 1.0 + _la ) ;
   _lb = alph (  _lv ) ;
   hinf = 1.0 / ( 1.0 + _lb ) ;
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  *getarg(1) ) ;
 ret(_r);
}
 
double alpm (  _lv )  
	double _lv ;
 {
   double _lalpm;
  _lalpm = exp ( 1.e-3 * zetam * ( _lv - vhalfm ) * 9.648e4 / ( 8.315 * ( 273.16 + celsius ) ) ) ;
    
return _lalpm;
 }
 static int _hoc_alpm() {
 double _r;
 _r =  alpm (  *getarg(1) ) ;
 ret(_r);
}
 
double alph (  _lv )  
	double _lv ;
 {
   double _lalph;
  _lalph = exp ( 1.e-3 * zetah * ( _lv - vhalfh ) * 9.648e4 / ( 8.315 * ( 273.16 + celsius ) ) ) ;
    
return _lalph;
 }
 static int _hoc_alph() {
 double _r;
 _r =  alph (  *getarg(1) ) ;
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
  h = h0;
  m = m0;
 {
   rates (  v ) ;
   m = minf ;
   h = hinf ;
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
   iCa = gcatbar * m * m * h * ( v - eca ) ;
   }
 _current += iCa;

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
 	{ static double _diCa;
  _diCa = iCa;
 _rhs = _nrn_current(_v);
  _ion_diCadv += (_diCa - iCa)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_iCa += iCa ;
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
 if(error){fprintf(stderr,"at line 66 in file cat.mod:\n:	ecat = (1e3) * (R*(celsius+273.15))/(2*FARADAY) * log (cao/cai)\n"); nrn_complain(_p); abort_run(error);}
 
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

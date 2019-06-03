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
#define gbar _p[0]
#define ik _p[1]
#define xs _p[2]
#define ys _p[3]
#define q10 _p[4]
#define T _p[5]
#define Dxs _p[6]
#define Dys _p[7]
#define _g _p[8]
#define _ion_ik	*_ppvar[0].pval
#define _ion_dikdv	*_ppvar[1].pval
 
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
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("kdBG");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_kdBG", _hoc_setdata,
 "rates_kdBG", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
#define Ky Ky_kdBG
 double Ky = 0.0002;
#define gammay gammay_kdBG
 double gammay = 0;
#define taoy taoy_kdBG
 double taoy = 0;
#define taox taox_kdBG
 double taox = 1;
#define vhalfy vhalfy_kdBG
 double vhalfy = -73;
#define vhalfx vhalfx_kdBG
 double vhalfx = -63;
#define xinf xinf_kdBG
 double xinf = 0;
#define xtau xtau_kdBG
 double xtau = 0;
#define yinf yinf_kdBG
 double yinf = 0;
#define ytau ytau_kdBG
 double ytau = 0;
#define zettay zettay_kdBG
 double zettay = -2.5;
#define zettax zettax_kdBG
 double zettax = 3;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "Ky_kdBG", "1/ms",
 "gammay_kdBG", "1",
 "zettax_kdBG", "1",
 "zettay_kdBG", "1",
 "vhalfx_kdBG", "mV",
 "vhalfy_kdBG", "mV",
 "taox_kdBG", "ms",
 "taoy_kdBG", "ms",
 "xtau_kdBG", "ms",
 "ytau_kdBG", "ms",
 "xinf_kdBG", "1",
 "yinf_kdBG", "1",
 "gbar_kdBG", "S/cm2",
 "ik_kdBG", "mA/cm2",
 0,0
};
 static double v = 0;
 static double xs0 = 0;
 static double ys0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "Ky_kdBG", &Ky,
 "gammay_kdBG", &gammay,
 "zettax_kdBG", &zettax,
 "zettay_kdBG", &zettay,
 "vhalfx_kdBG", &vhalfx,
 "vhalfy_kdBG", &vhalfy,
 "taox_kdBG", &taox,
 "taoy_kdBG", &taoy,
 "xtau_kdBG", &xtau,
 "ytau_kdBG", &ytau,
 "xinf_kdBG", &xinf,
 "yinf_kdBG", &yinf,
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
 
#define _cvode_ieq _ppvar[2]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.0.2",
"kdBG",
 "gbar_kdBG",
 0,
 "ik_kdBG",
 0,
 "xs_kdBG",
 "ys_kdBG",
 0,
 0};
 static Symbol* _k_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 9);
 	/*initialize range parameters*/
 	gbar = 0.001;
 	_prop->param = _p;
 	_prop->param_size = 9;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 	_ppvar[0].pval = &prop_ion->param[3]; /* ik */
 	_ppvar[1].pval = &prop_ion->param[4]; /* _ion_dikdv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _KdBG_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 3);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 kdBG /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/KdBG.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.31342;
static int _reset;
static char *modelname = "Kd current";

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
   rates (  ) ;
   Dxs = ( xinf - xs ) / xtau ;
   Dys = ( yinf - ys ) / ytau ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 rates (  ) ;
 Dxs = Dxs  / (1. - dt*( ( ( ( - 1.0 ) ) ) / xtau )) ;
 Dys = Dys  / (1. - dt*( ( ( ( - 1.0 ) ) ) / ytau )) ;
}
 /*END CVODE*/
 static int states () {_reset=0;
 {
   rates (  ) ;
    xs = xs + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / xtau)))*(- ( ( ( xinf ) ) / xtau ) / ( ( ( ( - 1.0) ) ) / xtau ) - xs) ;
    ys = ys + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / ytau)))*(- ( ( ( yinf ) ) / ytau ) / ( ( ( ( - 1.0) ) ) / ytau ) - ys) ;
   }
  return 0;
}
 
static int  rates (  )  {
   double _la , _lb ;
 _la = q10 * exp ( ( 1.0e-3 ) * zettax * ( v - vhalfx ) * FARADAY / ( R * T ) ) ;
   _lb = q10 * exp ( ( 1.0e-3 ) * - zettax * ( v - vhalfx ) * FARADAY / ( R * T ) ) ;
   xinf = _la / ( _la + _lb ) ;
   xtau = taox ;
   _la = q10 * Ky * exp ( ( 1.0e-3 ) * zettay * gammay * ( v - vhalfy ) * FARADAY / ( R * T ) ) ;
   _lb = q10 * Ky * exp ( ( 1.0e-3 ) * - zettay * ( 1.0 - gammay ) * ( v - vhalfy ) * FARADAY / ( R * T ) ) ;
   yinf = _la / ( _la + _lb ) ;
   ytau = 1.0 / ( _la + _lb ) + taoy ;
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 2;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
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
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  xs = xs0;
  ys = ys0;
 {
   T = celsius + 273.15 ;
   q10 = pow( 1.0 , ( ( celsius - 35.0 ) / 10.0 ) ) ;
   rates (  ) ;
   xs = xinf ;
   ys = yinf ;
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
 initmodel();
 }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   ik = gbar * pow( xs , 4.0 ) * pow( ys , 4.0 ) * ( v + 95.0 ) ;
   }
 _current += ik;

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
 _g = _nrn_current(_v + .001);
 	{ static double _dik;
  _dik = ik;
 _rhs = _nrn_current(_v);
  _ion_dikdv += (_dik - ik)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
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
 { {
 for (; t < _break; t += delta_t) {
 error =  states();
 if(error){fprintf(stderr,"at line 56 in file KdBG.mod:\n	SOLVE states METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(xs) - _p;  _dlist1[0] = &(Dxs) - _p;
 _slist1[1] = &(ys) - _p;  _dlist1[1] = &(Dys) - _p;
_first = 0;
}

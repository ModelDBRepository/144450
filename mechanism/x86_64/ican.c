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
#define in _p[1]
#define m_inf _p[2]
#define tau_m _p[3]
#define m _p[4]
#define en _p[5]
#define cai _p[6]
#define Dm _p[7]
#define tadj _p[8]
#define _g _p[9]
#define _ion_en	*_ppvar[0].pval
#define _ion_in	*_ppvar[1].pval
#define _ion_dindv	*_ppvar[2].pval
#define _ion_cai	*_ppvar[3].pval
 
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
 static int _hoc_evaluate_fct();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("ican");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_ican", _hoc_setdata,
 "evaluate_fct_ican", _hoc_evaluate_fct,
 0, 0
};
 /* declare global and static user variables */
#define beta beta_ican
 double beta = 0.001;
#define cac cac_ican
 double cac = 0.01;
#define taumin taumin_ican
 double taumin = 0.1;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "cac_ican", "mM",
 "taumin_ican", "ms",
 "gbar_ican", "mho/cm2",
 "in_ican", "mA/cm2",
 "tau_m_ican", "ms",
 0,0
};
 static double m0 = 0;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "beta_ican", &beta,
 "cac_ican", &cac,
 "taumin_ican", &taumin,
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
"ican",
 "gbar_ican",
 0,
 "in_ican",
 "m_inf_ican",
 "tau_m_ican",
 0,
 "m_ican",
 0,
 0};
 static Symbol* _n_sym;
 static Symbol* _ca_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 10);
 	/*initialize range parameters*/
 	gbar = 0.00025;
 	_prop->param = _p;
 	_prop->param_size = 10;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_n_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0].pval = &prop_ion->param[0]; /* en */
 	_ppvar[1].pval = &prop_ion->param[3]; /* in */
 	_ppvar[2].pval = &prop_ion->param[4]; /* _ion_dindv */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[3].pval = &prop_ion->param[1]; /* cai */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 _ican_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("n", 1.0);
 	ion_reg("ca", -10000.);
 	_n_sym = hoc_lookup("n_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 5);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 ican /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/ican.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Slow Ca-dependent cation current";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static evaluate_fct();
 
static int _ode_spec1(), _ode_matsol1();
 static double *_temp1;
 static int _slist1[1], _dlist1[1];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   evaluate_fct (  v , cai ) ;
   Dm = ( m_inf - m ) / tau_m ;
   }
 return _reset;
}
 static int _ode_matsol1() {
 evaluate_fct (  v , cai ) ;
 Dm = Dm  / (1. - dt*( ( ( ( - 1.0 ) ) ) / tau_m )) ;
}
 /*END CVODE*/
 
static int states () {_reset=0;
 {
   evaluate_fct (  v , cai ) ;
   Dm = ( m_inf - m ) / tau_m ;
   }
 return _reset;}
 
static int  evaluate_fct (  _lv , _lcai )  
	double _lv , _lcai ;
 {
   double _lalpha2 ;
 _lalpha2 = beta * pow( ( _lcai / cac ) , 2.0 ) ;
   tau_m = 1.0 / ( _lalpha2 + beta ) / tadj ;
   m_inf = _lalpha2 / ( _lalpha2 + beta ) ;
   if ( tau_m < taumin ) {
     tau_m = taumin ;
     }
    return 0; }
 static int _hoc_evaluate_fct() {
 double _r;
 _r = 1.;
 evaluate_fct (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 1;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  en = _ion_en;
  cai = _ion_cai;
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
  en = _ion_en;
  cai = _ion_cai;
 _ode_matsol1();
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  m = m0;
 {
   tadj = pow( 3.0 , ( ( celsius - 22.0 ) / 10.0 ) ) ;
   evaluate_fct (  v , cai ) ;
   m = m_inf ;
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
  en = _ion_en;
  cai = _ion_cai;
 initmodel();
 }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   in = gbar * m * m * ( v - en ) ;
   }
 _current += in;

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
  en = _ion_en;
  cai = _ion_cai;
 _g = _nrn_current(_v + .001);
 	{ static double _din;
  _din = in;
 _rhs = _nrn_current(_v);
  _ion_dindv += (_din - in)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_in += in ;
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
  en = _ion_en;
  cai = _ion_cai;
 { {
 for (; t < _break; t += delta_t) {
 error =  euler(_ninits, 1, _slist1, _dlist1, _p, &t, delta_t, states, &_temp1);
 if(error){fprintf(stderr,"at line 73 in file ican.mod:\n                                     SOLVE states METHOD euler\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
  states();
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m) - _p;  _dlist1[0] = &(Dm) - _p;
_first = 0;
}

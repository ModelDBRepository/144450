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
#define gkbar _p[0]
#define ik _p[1]
#define cst _p[2]
#define ost _p[3]
#define ist _p[4]
#define cai _p[5]
#define ek _p[6]
#define k1 _p[7]
#define k2 _p[8]
#define k3 _p[9]
#define k4 _p[10]
#define q10 _p[11]
#define Dcst _p[12]
#define Dost _p[13]
#define Dist _p[14]
#define _g _p[15]
#define _ion_ek	*_ppvar[0].pval
#define _ion_ik	*_ppvar[1].pval
#define _ion_dikdv	*_ppvar[2].pval
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
 static int _hoc_alpha();
 static int _hoc_alp();
 static int _hoc_rates();
 static int _mechtype;
extern int nrn_get_mechtype();
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range("mykca");
 _p = _prop->param; _ppvar = _prop->dparam;
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_mykca", _hoc_setdata,
 "alpha_mykca", _hoc_alpha,
 "alp_mykca", _hoc_alp,
 "rates_mykca", _hoc_rates,
 0, 0
};
#define alpha alpha_mykca
#define alp alp_mykca
 extern double alpha();
 extern double alp();
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gkbar_mykca", "S/cm2",
 "ik_mykca", "mA/cm2",
 0,0
};
 static double cst0 = 0;
 static double ist0 = 0;
 static double ost0 = 0;
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
"mykca",
 "gkbar_mykca",
 0,
 "ik_mykca",
 0,
 "cst_mykca",
 "ost_mykca",
 "ist_mykca",
 0,
 0};
 static Symbol* _k_sym;
 static Symbol* _ca_sym;
 
static nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 16);
 	/*initialize range parameters*/
 	gkbar = 0.001;
 	_prop->param = _p;
 	_prop->param_size = 16;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_k_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0].pval = &prop_ion->param[0]; /* ek */
 	_ppvar[1].pval = &prop_ion->param[3]; /* ik */
 	_ppvar[2].pval = &prop_ion->param[4]; /* _ion_dikdv */
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
 static _singlechan_declare1();
 _kct_reg() {
	int _vectorized = 0;
  _initlists();
 	ion_reg("k", -10000.);
 	ion_reg("ca", -10000.);
 	_k_sym = hoc_lookup("k_ion");
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, _vectorized);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
  hoc_register_dparam_size(_mechtype, 5);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 hoc_reg_singlechan(_mechtype, _singlechan_declare1);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 mykca /home/jg/ModelosNeuron/ProgramsNeuronCA1_JG/CleanVersion_CA1_JG_15Mar09/mechanism/x86_64/kct.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Kct current";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static rates();
 extern double *_getelm();
  
#define _MATELM1(row,col)	*(_getelm(row + 1, col + 1))
 
#define _RHS1(arg) _coef1[arg + 1]
 static double *_coef1;
  
#define _linmat1  1
 static void* _sparseobj1;
 static void* _cvsparseobj1;
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[3], _dlist1[3]; static double *_temp1;
 static int kin();
 
static int kin ()
 {_reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/delta_t;
for(_i=1;_i<3;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
  rates (  v , cai ) ;
    /* ~ cst <-> ost ( k3 , k4 )*/
 f_flux =  k3 * cst ;
 b_flux =  k4 * ost ;
 _RHS1( 1) -= (f_flux - b_flux);
 _RHS1( 2) += (f_flux - b_flux);
 
 _term =  k3 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  k4 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
   /* ~ ost <-> ist ( k1 , 0.0 )*/
 f_flux =  k1 * ost ;
 b_flux =  0.0 * ist ;
 _RHS1( 2) -= (f_flux - b_flux);
 
 _term =  k1 ;
 _MATELM1( 2 ,2)  += _term;
 _term =  0.0 ;
 _MATELM1( 2 ,0)  -= _term;
 /*REACTION*/
   /* ~ ist <-> cst ( k2 , 0.0 )*/
 f_flux =  k2 * ist ;
 b_flux =  0.0 * cst ;
 _RHS1( 1) += (f_flux - b_flux);
 
 _term =  k2 ;
 _MATELM1( 1 ,0)  -= _term;
 _term =  0.0 ;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
    /* cst + ost + ist = 1.0 */
 _RHS1(0) =  1.0;
 _MATELM1(0, 0) = 1;
 _RHS1(0) -= ist ;
 _MATELM1(0, 2) = 1;
 _RHS1(0) -= ost ;
 _MATELM1(0, 1) = 1;
 _RHS1(0) -= cst ;
 /*CONSERVATION*/
   } return _reset;
 }
 
static int  rates (  _lv , _lcai )  
	double _lv , _lcai ;
 {
   k1 = alp (  0.1 , _lv , - 10.0 , 1.0 ) ;
   k2 = alp (  0.1 , _lv , - 120.0 , - 10.0 ) ;
   k3 = alpha (  0.001 , 1.0 , _lv , - 20.0 , 7.0 ) * 1.0e8 * pow( ( _lcai * 1.0 ) , 3.0 ) ;
   k4 = alp (  0.01 , _lv , - 44.0 , - 5.0 ) ;
    return 0; }
 static int _hoc_rates() {
 double _r;
 _r = 1.;
 rates (  *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
double alpha (  _ltmin , _ltmax , _lv , _lvhalf , _lk )  
	double _ltmin , _ltmax , _lv , _lvhalf , _lk ;
 {
   double _lalpha;
 _lalpha = 1.0 / ( _ltmin + 1.0 / ( 1.0 / ( _ltmax - _ltmin ) + exp ( ( _lv - _lvhalf ) / _lk ) * 1.0 ) ) ;
   
return _lalpha;
 }
 static int _hoc_alpha() {
 double _r;
 _r =  alpha (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) ) ;
 ret(_r);
}
 
double alp (  _ltmin , _lv , _lvhalf , _lk )  
	double _ltmin , _lv , _lvhalf , _lk ;
 {
   double _lalp;
 _lalp = 1.0 / ( _ltmin + exp ( - ( _lv - _lvhalf ) / _lk ) * 1.0 ) ;
   
return _lalp;
 }
 static int _hoc_alp() {
 double _r;
 _r =  alp (  *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) ) ;
 ret(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<3;_i++) _p[_dlist1[_i]] = 0.0;}
  rates (  v , cai ) ;
  /* ~ cst <-> ost ( k3 , k4 )*/
 f_flux =  k3 * cst ;
 b_flux =  k4 * ost ;
 Dcst -= (f_flux - b_flux);
 Dost += (f_flux - b_flux);
 
 /*REACTION*/
   /* ~ ost <-> ist ( k1 , 0.0 )*/
 f_flux =  k1 * ost ;
 b_flux =  0.0 * ist ;
 Dost -= (f_flux - b_flux);
 Dist += (f_flux - b_flux);
 
 /*REACTION*/
   /* ~ ist <-> cst ( k2 , 0.0 )*/
 f_flux =  k2 * ist ;
 b_flux =  0.0 * cst ;
 Dist -= (f_flux - b_flux);
 Dcst += (f_flux - b_flux);
 
 /*REACTION*/
    /* cst + ost + ist = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1() {_reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<3;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
} }
  rates (  v , cai ) ;
  /* ~ cst <-> ost ( k3 , k4 )*/
 _term =  k3 ;
 _MATELM1( 1 ,1)  += _term;
 _MATELM1( 2 ,1)  -= _term;
 _term =  k4 ;
 _MATELM1( 1 ,2)  -= _term;
 _MATELM1( 2 ,2)  += _term;
 /*REACTION*/
   /* ~ ost <-> ist ( k1 , 0.0 )*/
 _term =  k1 ;
 _MATELM1( 2 ,2)  += _term;
 _MATELM1( 0 ,2)  -= _term;
 _term =  0.0 ;
 _MATELM1( 2 ,0)  -= _term;
 _MATELM1( 0 ,0)  += _term;
 /*REACTION*/
   /* ~ ist <-> cst ( k2 , 0.0 )*/
 _term =  k2 ;
 _MATELM1( 0 ,0)  += _term;
 _MATELM1( 1 ,0)  -= _term;
 _term =  0.0 ;
 _MATELM1( 0 ,1)  -= _term;
 _MATELM1( 1 ,1)  += _term;
 /*REACTION*/
    /* cst + ost + ist = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
/*CVODE end*/
 
/*Single Channel begin*/
 static int _singlechan1(_v, _pp, _ppd) double _v; double* _pp; Datum* _ppd;{
	_p = _pp; _ppvar = _ppd; v = _v; _reset=0;
{
 double b_flux, f_flux, _term; int _i;
  rates (  v , cai ) ;
  /* ~ cst <-> ost ( k3 , k4 )*/
  _nrn_single_react(1 ,2 ,  k3);
  _nrn_single_react(2 ,1 ,  k4);
 /*REACTION*/
   /* ~ ost <-> ist ( k1 , 0.0 )*/
  _nrn_single_react(2 ,0 ,  k1);
  _nrn_single_react(0 ,2 ,  0.0);
 /*REACTION*/
   /* ~ ist <-> cst ( k2 , 0.0 )*/
  _nrn_single_react(0 ,1 ,  k2);
  _nrn_single_react(1 ,0 ,  0.0);
 /*REACTION*/
    /* cst + ost + ist = 1.0 */
 /*CONSERVATION*/
   } return _reset;
 }
 
static _singlechan_declare1() {
	_singlechan_declare(_singlechan1, _slist1, 3);
}
 
/*Single Channel end*/
 
static int _ode_count(_type) int _type;{ return 3;}
 
static int _ode_spec(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  ek = _ion_ek;
  cai = _ion_cai;
  _ode_spec1();
  }
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; {
	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 3; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static int _ode_matsol(_nd, _pp, _ppd) Node* _nd; double* _pp; Datum* _ppd; {
	_p = _pp; _ppvar = _ppd; v = NODEV(_nd);
  ek = _ion_ek;
  cai = _ion_cai;
 _cvode_sparse(&_cvsparseobj1, 3, _dlist1, _p, _ode_matsol1, &_coef1);
 }

static initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  cst = cst0;
  ist = ist0;
  ost = ost0;
 {
   error = _ss_sparse(&_sparseobj1, 3, _slist1, _dlist1, _p, &t, delta_t, kin,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 55 in file kct.mod:\n	SOLVE kin STEADYSTATE sparse\n"); nrn_complain(_p); abort_run(error);}
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
  ek = _ion_ek;
  cai = _ion_cai;
 initmodel();
 }}

static double _nrn_current(_v) double _v;{double _current=0.;v=_v;{ {
   ik = gkbar * ost * ( v - ek ) ;
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
  ek = _ion_ek;
  cai = _ion_cai;
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
  ek = _ion_ek;
  cai = _ion_cai;
 { {
 for (; t < _break; t += delta_t) {
 error = sparse(&_sparseobj1, 3, _slist1, _dlist1, _p, &t, delta_t, kin,&_coef1, _linmat1);
 if(error){fprintf(stderr,"at line 50 in file kct.mod:\n	SOLVE kin METHOD sparse\n"); nrn_complain(_p); abort_run(error);}
 
}}
 t = _save;
 } }}

}

static terminal(){}

static _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ist) - _p;  _dlist1[0] = &(Dist) - _p;
 _slist1[1] = &(cst) - _p;  _dlist1[1] = &(Dcst) - _p;
 _slist1[2] = &(ost) - _p;  _dlist1[2] = &(Dost) - _p;
_first = 0;
}

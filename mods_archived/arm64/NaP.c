/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__NaP
#define _nrn_initial _nrn_initial__NaP
#define nrn_cur _nrn_cur__NaP
#define _nrn_current _nrn_current__NaP
#define nrn_jacob _nrn_jacob__NaP
#define nrn_state _nrn_state__NaP
#define _net_receive _net_receive__NaP 
#define rates rates__NaP 
#define states states__NaP 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define g_nap_bar _p[0]
#define g_nap_bar_columnindex 0
#define DA _p[1]
#define DA_columnindex 1
#define m_nap_inf _p[2]
#define m_nap_inf_columnindex 2
#define h_nap_inf _p[3]
#define h_nap_inf_columnindex 3
#define m_nap_tau _p[4]
#define m_nap_tau_columnindex 4
#define h_nap_tau _p[5]
#define h_nap_tau_columnindex 5
#define m_nap _p[6]
#define m_nap_columnindex 6
#define h_nap _p[7]
#define h_nap_columnindex 7
#define ena _p[8]
#define ena_columnindex 8
#define Dm_nap _p[9]
#define Dm_nap_columnindex 9
#define Dh_nap _p[10]
#define Dh_nap_columnindex 10
#define ina _p[11]
#define ina_columnindex 11
#define v _p[12]
#define v_columnindex 12
#define _g _p[13]
#define _g_columnindex 13
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_rates(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_NaP", _hoc_setdata,
 "rates_NaP", _hoc_rates,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "g_nap_bar_NaP", "S/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double h_nap0 = 0;
 static double m_nap0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"NaP",
 "g_nap_bar_NaP",
 "DA_NaP",
 0,
 "m_nap_inf_NaP",
 "h_nap_inf_NaP",
 "m_nap_tau_NaP",
 "h_nap_tau_NaP",
 0,
 "m_nap_NaP",
 "h_nap_NaP",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 14, _prop);
 	/*initialize range parameters*/
 	g_nap_bar = 0.005;
 	DA = 0;
 	_prop->param = _p;
 	_prop->param_size = 14;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _NaP_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 14, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 NaP /Users/ryu/Documents/Project/Population Coding/codes/mods/NaP.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   Dm_nap = ( m_nap_inf - m_nap ) / m_nap_tau ;
   Dh_nap = ( h_nap_inf - h_nap ) / h_nap_tau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 Dm_nap = Dm_nap  / (1. - dt*( ( ( ( - 1.0 ) ) ) / m_nap_tau )) ;
 Dh_nap = Dh_nap  / (1. - dt*( ( ( ( - 1.0 ) ) ) / h_nap_tau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
    m_nap = m_nap + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / m_nap_tau)))*(- ( ( ( m_nap_inf ) ) / m_nap_tau ) / ( ( ( ( - 1.0 ) ) ) / m_nap_tau ) - m_nap) ;
    h_nap = h_nap + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / h_nap_tau)))*(- ( ( ( h_nap_inf ) ) / h_nap_tau ) / ( ( ( ( - 1.0 ) ) ) / h_nap_tau ) - h_nap) ;
   }
  return 0;
}
 
static int  rates ( _threadargsprotocomma_ double _lv ) {
   double _lalpha_m , _lbeta_m , _lalpha_h , _lbeta_h ;
 if ( DA  == 0.0 ) {
     _lalpha_m = - 0.2816 * ( _lv + 12.0 ) / ( 1.0 - exp ( - ( _lv + 12.0 ) / 9.3 ) ) ;
     _lbeta_m = 0.2464 * ( _lv - 15.0 ) / ( 1.0 - exp ( ( _lv - 15.0 ) / 6.0 ) ) ;
     _lalpha_h = 2.8e-5 * exp ( - ( _lv + 42.8477 ) / 4.0248 ) ;
     _lbeta_h = 0.02 / ( 1.0 + exp ( - ( _lv - 413.9284 ) / 148.2589 ) ) ;
     }
   else {
     _lalpha_m = - 0.2816 * ( _lv + 17.0 ) / ( 1.0 - exp ( - ( _lv + 17.0 ) / 9.3 ) ) ;
     _lbeta_m = 0.2464 * ( _lv - 10.0 ) / ( 1.0 - exp ( ( _lv - 10.0 ) / 6.0 ) ) ;
     _lalpha_h = 2.0e-5 * exp ( - ( _lv + 42.8477 ) / 4.0248 ) ;
     _lbeta_h = 0.014286 / ( 1.0 + exp ( - ( _lv - 413.9284 ) / 148.2589 ) ) ;
     }
   m_nap_inf = _lalpha_m / ( _lalpha_m + _lbeta_m ) ;
   h_nap_inf = _lalpha_h / ( _lalpha_h + _lbeta_h ) ;
   m_nap_tau = 1.0 / ( _lalpha_m + _lbeta_m ) ;
   h_nap_tau = 1.0 / ( _lalpha_h + _lbeta_h ) ;
    return 0; }
 
static void _hoc_rates(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  h_nap = h_nap0;
  m_nap = m_nap0;
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   ina = g_nap_bar * m_nap * h_nap * ( v - ena ) ;
   }
 _current += ina;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
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
 v=_v;
{
  ena = _ion_ena;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = m_nap_columnindex;  _dlist1[0] = Dm_nap_columnindex;
 _slist1[1] = h_nap_columnindex;  _dlist1[1] = Dh_nap_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/ryu/Documents/Project/Population Coding/codes/mods/NaP.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "    SUFFIX NaP\n"
  "    USEION na READ ena WRITE ina\n"
  "    RANGE g_nap_bar, m_nap_inf, h_nap_inf, m_nap_tau, h_nap_tau, DA\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    g_nap_bar = 0.005 (S/cm2)\n"
  "    DA = 0  : 0% DA (Default), set to 1 for 100% DA\n"
  "    ena = 50 (mV)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "    m_nap h_nap\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v (volt)\n"
  "    ina (mA/cm2)\n"
  "    m_nap_inf h_nap_inf m_nap_tau h_nap_tau\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    SOLVE states METHOD cnexp\n"
  "    ina = g_nap_bar * m_nap * h_nap * (v - ena)\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "    m_nap' = (m_nap_inf - m_nap) / m_nap_tau\n"
  "    h_nap' = (h_nap_inf - h_nap) / h_nap_tau\n"
  "}\n"
  "\n"
  "PROCEDURE rates(v (mV)) {\n"
  "    LOCAL alpha_m, beta_m, alpha_h, beta_h\n"
  "    \n"
  "    if (DA == 0) {  : 0% DA\n"
  "        alpha_m = -0.2816 * (v + 12) / (1 - exp(-(v + 12) / 9.3))\n"
  "        beta_m = 0.2464 * (v - 15) / (1 - exp((v - 15) / 6))\n"
  "\n"
  "        alpha_h = 2.8e-5 * exp(-(v + 42.8477) / 4.0248)\n"
  "        beta_h = 0.02 / (1 + exp(-(v - 413.9284) / 148.2589))\n"
  "    } else {  : 100% DA\n"
  "        alpha_m = -0.2816 * (v + 17) / (1 - exp(-(v + 17) / 9.3))\n"
  "        beta_m = 0.2464 * (v - 10) / (1 - exp((v - 10) / 6))\n"
  "\n"
  "        alpha_h = 2.0e-5 * exp(-(v + 42.8477) / 4.0248)\n"
  "        beta_h = 0.014286 / (1 + exp(-(v - 413.9284) / 148.2589))\n"
  "    }\n"
  "    \n"
  "    m_nap_inf = alpha_m / (alpha_m + beta_m)\n"
  "    h_nap_inf = alpha_h / (alpha_h + beta_h)\n"
  "\n"
  "    m_nap_tau = 1 / (alpha_m + beta_m)\n"
  "    h_nap_tau = 1 / (alpha_h + beta_h)\n"
  "}\n"
  "\n"
  ;
#endif

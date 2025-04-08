/* Created by Language version: 7.7.0 */
/* NOT VECTORIZED */
#define NRN_VECTORIZED 0
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
 
#define nrn_init _nrn_init__STDPsyn
#define _nrn_initial _nrn_initial__STDPsyn
#define nrn_cur _nrn_cur__STDPsyn
#define _nrn_current _nrn_current__STDPsyn
#define nrn_jacob _nrn_jacob__STDPsyn
#define nrn_state _nrn_state__STDPsyn
#define _net_receive _net_receive__STDPsyn 
#define state state__STDPsyn 
 
#define _threadargscomma_ /**/
#define _threadargsprotocomma_ /**/
#define _threadargs_ /**/
#define _threadargsproto_ /**/
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 static double *_p; static Datum *_ppvar;
 
#define t nrn_threads->_t
#define dt nrn_threads->_dt
#define tau1 _p[0]
#define tau1_columnindex 0
#define tau2 _p[1]
#define tau2_columnindex 1
#define e _p[2]
#define e_columnindex 2
#define gmax _p[3]
#define gmax_columnindex 3
#define USE _p[4]
#define USE_columnindex 4
#define trec _p[5]
#define trec_columnindex 5
#define wn _p[6]
#define wn_columnindex 6
#define i _p[7]
#define i_columnindex 7
#define g _p[8]
#define g_columnindex 8
#define A _p[9]
#define A_columnindex 9
#define B _p[10]
#define B_columnindex 10
#define factor _p[11]
#define factor_columnindex 11
#define DA _p[12]
#define DA_columnindex 12
#define DB _p[13]
#define DB_columnindex 13
#define _g _p[14]
#define _g_columnindex 14
#define _tsav _p[15]
#define _tsav_columnindex 15
#define _nd_area  *_ppvar[0]._pval
 
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
 /* external NEURON variables */
 /* declaration of user functions */
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

 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(Object* _ho) { void* create_point_process(int, Object*);
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt(void*);
 static double _hoc_loc_pnt(void* _vptr) {double loc_point_process(int, void*);
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(void* _vptr) {double has_loc_point(void*);
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(void* _vptr) {
 double get_loc_point_process(void*); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _p = _prop->param; _ppvar = _prop->dparam;
 }
 static void _hoc_setdata(void* _vptr) { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 0,0
};
 static Member_func _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
#define A_LTD A_LTD_STDPsyn
 double A_LTD = 0.005;
#define A_LTP A_LTP_STDPsyn
 double A_LTP = 0.005;
#define tau_LTD tau_LTD_STDPsyn
 double tau_LTD = 30;
#define tau_LTP tau_LTP_STDPsyn
 double tau_LTP = 20;
#define tlast tlast_STDPsyn
 double tlast = 0;
#define wmax wmax_STDPsyn
 double wmax = 2;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "tau_LTP_STDPsyn", "ms",
 "tau_LTD_STDPsyn", "ms",
 "tlast_STDPsyn", "ms",
 "tau1", "ms",
 "tau2", "ms",
 "e", "mV",
 "gmax", "uS",
 "trec", "ms",
 "i", "nA",
 "g", "uS",
 0,0
};
 static double A0 = 0;
 static double B0 = 0;
 static double delta_t = 0.01;
 static double v = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "wmax_STDPsyn", &wmax_STDPsyn,
 "tau_LTP_STDPsyn", &tau_LTP_STDPsyn,
 "tau_LTD_STDPsyn", &tau_LTD_STDPsyn,
 "A_LTP_STDPsyn", &A_LTP_STDPsyn,
 "A_LTD_STDPsyn", &A_LTD_STDPsyn,
 "tlast_STDPsyn", &tlast_STDPsyn,
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
 static void _hoc_destroy_pnt(void* _vptr) {
   destroy_point_process(_vptr);
}
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[2]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"STDPsyn",
 "tau1",
 "tau2",
 "e",
 "gmax",
 "USE",
 "trec",
 "wn",
 0,
 "i",
 "g",
 0,
 "A",
 "B",
 0,
 0};
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 16, _prop);
 	/*initialize range parameters*/
 	tau1 = 0.5;
 	tau2 = 3;
 	e = 0;
 	gmax = 0.004;
 	USE = 0.6;
 	trec = 800;
 	wn = 1;
  }
 	_prop->param = _p;
 	_prop->param_size = 16;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 3, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _net_receive(Point_process*, double*, double);
 static void _net_init(Point_process*, double*, double);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _stdp_syn_reg() {
	int _vectorized = 0;
  _initlists();
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex, 0,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 16, 3);
  hoc_register_dparam_semantics(_mechtype, 0, "area");
  hoc_register_dparam_semantics(_mechtype, 1, "pntproc");
  hoc_register_dparam_semantics(_mechtype, 2, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_init[_mechtype] = _net_init;
 pnt_receive_size[_mechtype] = 4;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 STDPsyn /Users/ryu/Documents/Project/Population Coding/codes/mods/stdp_syn.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[2], _dlist1[2];
 static int state(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 () {_reset=0;
 {
   DA = - A / tau1 ;
   DB = - B / tau2 ;
   }
 return _reset;
}
 static int _ode_matsol1 () {
 DA = DA  / (1. - dt*( ( - 1.0 ) / tau1 )) ;
 DB = DB  / (1. - dt*( ( - 1.0 ) / tau2 )) ;
  return 0;
}
 /*END CVODE*/
 static int state () {_reset=0;
 {
    A = A + (1. - exp(dt*(( - 1.0 ) / tau1)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau1 ) - A) ;
    B = B + (1. - exp(dt*(( - 1.0 ) / tau2)))*(- ( 0.0 ) / ( ( - 1.0 ) / tau2 ) - B) ;
   }
  return 0;
}
 
static void _net_receive (Point_process* _pnt, double* _args, double _lflag) 
{    _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t; {
   double _ldt , _lw_change ;
 _ldt = t - _args[3] ;
   if ( _ldt > 0.0 ) {
     _args[2] = 1.0 - ( 1.0 - _args[2] ) * exp ( - _ldt / trec ) ;
     _args[1] = USE + ( 1.0 - USE ) * _args[1] * exp ( - _ldt / trec ) ;
     _args[2] = _args[2] - _args[1] * _args[2] ;
       if (nrn_netrec_state_adjust && !cvode_active_){
    /* discon state adjustment for cnexp case (rate uses no local variable) */
    double __state = A;
    double __primary = (A + factor * _args[1] * _args[2]) - __state;
     __primary += ( 1. - exp( 0.5*dt*( ( - 1.0 ) / tau1 ) ) )*( - ( 0.0 ) / ( ( - 1.0 ) / tau1 ) - __primary );
    A += __primary;
  } else {
 A = A + factor * _args[1] * _args[2] ;
       }
   if (nrn_netrec_state_adjust && !cvode_active_){
    /* discon state adjustment for cnexp case (rate uses no local variable) */
    double __state = B;
    double __primary = (B + factor * _args[1] * _args[2]) - __state;
     __primary += ( 1. - exp( 0.5*dt*( ( - 1.0 ) / tau2 ) ) )*( - ( 0.0 ) / ( ( - 1.0 ) / tau2 ) - __primary );
    B += __primary;
  } else {
 B = B + factor * _args[1] * _args[2] ;
       }
 _args[3] = t ;
     }
   if ( tlast > - 1e9 ) {
     _ldt = t - tlast ;
     if ( _ldt > 0.0 ) {
       _lw_change = A_LTP * exp ( - _ldt / tau_LTP ) ;
       }
     else {
       _lw_change = - A_LTD * exp ( _ldt / tau_LTD ) ;
       }
     wn = wn + _lw_change ;
     if ( wn > wmax ) {
       wn = wmax ;
       }
     else if ( wn < 0.0 ) {
       wn = 0.0 ;
       }
     }
   tlast = t ;
   } }
 
static void _net_init(Point_process* _pnt, double* _args, double _lflag) {
       _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
 _args[1] = USE ;
   _args[2] = 1.0 ;
   _args[3] = - 1e9 ;
   }
 
static int _ode_count(int _type){ return 2;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
     _ode_spec1 ();
 }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 ();
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
 _ode_matsol_instance1(_threadargs_);
 }}

static void initmodel() {
  int _i; double _save;_ninits++;
 _save = t;
 t = 0.0;
{
  A = A0;
  B = B0;
 {
   double _ltp ;
 A = 0.0 ;
   B = 0.0 ;
   tlast = - 1e9 ;
   _ltp = ( tau1 * tau2 ) / ( tau2 - tau1 ) * log ( tau2 / tau1 ) ;
   factor = 1.0 / ( - exp ( - _ltp / tau1 ) + exp ( - _ltp / tau2 ) ) ;
   }
  _sav_indep = t; t = _save;

}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _tsav = -1e20;
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

static double _nrn_current(double _v){double _current=0.;v=_v;{ {
   g = gmax * wn * ( B - A ) ;
   i = g * ( v - e ) ;
   }
 _current += i;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type){
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
 	{ _rhs = _nrn_current(_v);
 	}
 _g = (_g - _rhs)/.001;
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type){
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

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type){
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
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
 v=_v;
{
 { error =  state();
 if(error){fprintf(stderr,"at line 47 in file stdp_syn.mod:\n    SOLVE state METHOD cnexp\n"); nrn_complain(_p); abort_run(error);}
 }}}

}

static void terminal(){}

static void _initlists() {
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = A_columnindex;  _dlist1[0] = DA_columnindex;
 _slist1[1] = B_columnindex;  _dlist1[1] = DB_columnindex;
_first = 0;
}

#if NMODL_TEXT
static const char* nmodl_filename = "/Users/ryu/Documents/Project/Population Coding/codes/mods/stdp_syn.mod";
static const char* nmodl_file_text = 
  "NEURON {\n"
  "    POINT_PROCESS STDPsyn\n"
  "    NONSPECIFIC_CURRENT i\n"
  "    RANGE tau1, tau2, e, gmax, g, wn, USE, trec\n"
  "    GLOBAL tlast, wmax, tau_LTP, tau_LTD, A_LTP, A_LTD\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "    tau1 = 0.5 (ms)   : Rise time constant\n"
  "    tau2 = 3.0 (ms)   : Decay time constant\n"
  "    e = 0 (mV)        : Reversal potential\n"
  "    gmax = 4e-3 (uS)  : Maximal AMPA conductance\n"
  "    USE = 0.6         : Utilization parameter for short-term depression\n"
  "    trec = 800 (ms)   : Recovery time constant\n"
  "    wn = 1.0          : Synaptic efficacy (plastic weight)\n"
  "    \n"
  "    wmax = 2.0        : Maximum synaptic weight\n"
  "    tau_LTP = 20.0 (ms) : Time constant for LTP\n"
  "    tau_LTD = 30.0 (ms) : Time constant for LTD\n"
  "    A_LTP = 0.005       : LTP learning rate\n"
  "    A_LTD = 0.005       : LTD learning rate\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "    v (mV)      : Membrane voltage\n"
  "    i (nA)      : Synaptic current\n"
  "    g (uS)      : Conductance\n"
  "    factor      : Normalization factor\n"
  "    tlast (ms)  : Last spike time\n"
  "}\n"
  "\n"
  "STATE {\n"
  "    A\n"
  "    B\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "    LOCAL tp\n"
  "    A = 0\n"
  "    B = 0\n"
  "    tlast = -1e9\n"
  "    tp = (tau1*tau2)/(tau2 - tau1) * log(tau2/tau1)\n"
  "    factor = 1.0 / (-exp(-tp/tau1) + exp(-tp/tau2))  : Normalize peak\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "    SOLVE state METHOD cnexp\n"
  "    g = gmax * wn * (B - A)\n"
  "    i = g * (v - e)\n"
  "}\n"
  "\n"
  "DERIVATIVE state {\n"
  "    A' = -A / tau1\n"
  "    B' = -B / tau2\n"
  "}\n"
  "\n"
  "NET_RECEIVE (weight (uS), u, R, last_release) {\n"
  "\n"
  "    LOCAL dt, w_change\n"
  "\n"
  "    INITIAL {\n"
  "        u = USE\n"
  "        R = 1\n"
  "        last_release = -1e9\n"
  "    }\n"
  "\n"
  "    dt = t - last_release\n"
  "    if (dt > 0) {\n"
  "        R = 1 - (1 - R) * exp(-dt / trec)\n"
  "        u = USE + (1 - USE) * u * exp(-dt / trec)\n"
  "        R = R - u * R\n"
  "        A = A + factor * u * R\n"
  "        B = B + factor * u * R\n"
  "        last_release = t\n"
  "    }\n"
  "\n"
  "    : STDP update\n"
  "    if (tlast > -1e9) {\n"
  "        dt = t - tlast\n"
  "        if (dt > 0) {\n"
  "            w_change = A_LTP * exp(-dt / tau_LTP)\n"
  "        } else {\n"
  "            w_change = -A_LTD * exp(dt / tau_LTD)\n"
  "        }\n"
  "        wn = wn + w_change\n"
  "        if (wn > wmax) {\n"
  "            wn = wmax\n"
  "        } else if (wn < 0) {\n"
  "            wn = 0\n"
  "        }\n"
  "    }\n"
  "    tlast = t\n"
  "}\n"
  ;
#endif

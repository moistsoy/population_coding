#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _C_reg(void);
extern void _DR_reg(void);
extern void _HVA_reg(void);
extern void _KS_reg(void);
extern void _Na_reg(void);
extern void _NaP_reg(void);
extern void _cadyn_reg(void);
extern void _kdyn_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"C.mod\"");
    fprintf(stderr, " \"DR.mod\"");
    fprintf(stderr, " \"HVA.mod\"");
    fprintf(stderr, " \"KS.mod\"");
    fprintf(stderr, " \"Na.mod\"");
    fprintf(stderr, " \"NaP.mod\"");
    fprintf(stderr, " \"cadyn.mod\"");
    fprintf(stderr, " \"kdyn.mod\"");
    fprintf(stderr, "\n");
  }
  _C_reg();
  _DR_reg();
  _HVA_reg();
  _KS_reg();
  _Na_reg();
  _NaP_reg();
  _cadyn_reg();
  _kdyn_reg();
}

#if defined(__cplusplus)
}
#endif

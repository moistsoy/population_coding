#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
#if defined(__cplusplus)
extern "C" {
#endif

extern void _cadyn_reg(void);
extern void _hva_reg(void);
extern void _ic_reg(void);
extern void _iks_reg(void);
extern void _kdr_reg(void);
extern void _kdyn_reg(void);
extern void _naf_reg(void);
extern void _nap_reg(void);

void modl_reg() {
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");
    fprintf(stderr, " \"cadyn.mod\"");
    fprintf(stderr, " \"hva.mod\"");
    fprintf(stderr, " \"ic.mod\"");
    fprintf(stderr, " \"iks.mod\"");
    fprintf(stderr, " \"kdr.mod\"");
    fprintf(stderr, " \"kdyn.mod\"");
    fprintf(stderr, " \"naf.mod\"");
    fprintf(stderr, " \"nap.mod\"");
    fprintf(stderr, "\n");
  }
  _cadyn_reg();
  _hva_reg();
  _ic_reg();
  _iks_reg();
  _kdr_reg();
  _kdyn_reg();
  _naf_reg();
  _nap_reg();
}

#if defined(__cplusplus)
}
#endif

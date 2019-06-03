#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;
modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," ampa.mod");
    fprintf(stderr," cad.mod");
    fprintf(stderr," calH.mod");
    fprintf(stderr," cal.mod");
    fprintf(stderr," can.mod");
    fprintf(stderr," car.mod");
    fprintf(stderr," cat.mod");
    fprintf(stderr," d3.mod");
    fprintf(stderr," gabaa.mod");
    fprintf(stderr," gabab.mod");
    fprintf(stderr," hha2.mod");
    fprintf(stderr," hha_old.mod");
    fprintf(stderr," h.mod");
    fprintf(stderr," ican.mod");
    fprintf(stderr," ipulse1.mod");
    fprintf(stderr," ipulse2.mod");
    fprintf(stderr," kadist.mod");
    fprintf(stderr," kaprox.mod");
    fprintf(stderr," kca.mod");
    fprintf(stderr," kct.mod");
    fprintf(stderr," KdBG.mod");
    fprintf(stderr," km.mod");
    fprintf(stderr," nap.mod");
    fprintf(stderr," netstimmm.mod");
    fprintf(stderr," netstim.mod");
    fprintf(stderr," NMDAb.mod");
    fprintf(stderr," nmda.mod");
    fprintf(stderr," somacar.mod");
    fprintf(stderr, "\n");
  }
  _ampa_reg();
  _cad_reg();
  _calH_reg();
  _cal_reg();
  _can_reg();
  _car_reg();
  _cat_reg();
  _d3_reg();
  _gabaa_reg();
  _gabab_reg();
  _hha2_reg();
  _hha_old_reg();
  _h_reg();
  _ican_reg();
  _ipulse1_reg();
  _ipulse2_reg();
  _kadist_reg();
  _kaprox_reg();
  _kca_reg();
  _kct_reg();
  _KdBG_reg();
  _km_reg();
  _nap_reg();
  _netstimmm_reg();
  _netstim_reg();
  _NMDAb_reg();
  _nmda_reg();
  _somacar_reg();
}

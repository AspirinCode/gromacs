/*
 * $Id$
 * 
 *                This source code is part of
 * 
 *                 G   R   O   M   A   C   S
 * 
 *          GROningen MAchine for Chemical Simulations
 * 
 *                        VERSION 3.2.0
 * Written by David van der Spoel, Erik Lindahl, Berk Hess, and others.
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2004, The GROMACS development team,
 * check out http://www.gromacs.org for more information.

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * If you want to redistribute modifications, please consider that
 * scientific software is very special. Version control is crucial -
 * bugs must be traceable. We will be happy to consider code for
 * inclusion in the official distribution, but derived work must not
 * be called official GROMACS. Details are found in the README & COPYING
 * files - if they are missing, get the official version at www.gromacs.org.
 * 
 * To help us fund GROMACS development, we humbly ask that you cite
 * the papers on the package - you can find them in the top README file.
 * 
 * For more info, check our website at http://www.gromacs.org
 * 
 * And Hey:
 * Gromacs Runs On Most of All Computer Systems
 */

#ifndef _mdrun_h
#define _mdrun_h

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include "typedefs.h"
#include "network.h"
#include "tgroup.h"
#include "filenm.h"
#include "mshift.h"
#include "force.h"
#include "time.h"
#include "edsam.h"
#include "mdebin.h"
#include "vcm.h"
#include "vsite.h"
#include "pull.h"

#define MD_GLAS        (1<<1)
#define MD_POLARISE    (1<<2)
#define MD_IONIZE      (1<<3)
#define MD_RERUN       (1<<4)
#define MD_FFSCAN      (1<<6)
#define MD_SEPDVDL     (1<<7)
#define MD_CARTESIAN   (1<<8)
#define MD_ORD_PP_PME  (1<<9)
#define MD_DLB         (1<<10)

/* ROUTINES from md.c */
extern time_t do_md(FILE *log,t_commrec *cr,
		    int nfile,t_filenm fnm[],
		    bool bVerbose,bool bCompact,
		    ivec ddxyz,char *loadx,char *loady,char *loadz,
		    bool bVsites,t_comm_vsites *vsitecomm,int stepout,
		    t_inputrec *inputrec,t_groups *grps,
		    t_topology *top,real ener[],t_fcdata *fcd,
		    t_state *state,rvec f[],
		    rvec buf[],t_mdatoms *mdatoms,
		    t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		    t_graph *graph,t_edsamyn *edyn,
		    t_forcerec *fr,
		    int repl_ex_nst,int repl_ex_seed,
		    unsigned long Flags);

/* ROUTINES from minimize.c */
extern time_t do_steep(FILE *log,int nfile,t_filenm fnm[],
		       t_inputrec *inputrec,t_topology *top,
		       t_groups *grps,
		       t_state *state,rvec grad[],rvec buf[],t_mdatoms *mdatoms,
		       real ener[],t_fcdata *fcd,
		       t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		       bool bVerbose,bool bVsites,t_comm_vsites *vsitecomm,
		       t_commrec *cr,
		       t_graph *graph,t_forcerec *fr);
/* Do steepest descents EM or something like that! */

extern time_t do_cg(FILE *log,int nfile,t_filenm fnm[],
		    t_inputrec *inputrec,t_topology *top,
		    t_groups *grps,
		    t_state *state,rvec grad[],rvec buf[],t_mdatoms *mdatoms,
		    real ener[],t_fcdata *fcd,
		    t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		    bool bVerbose,bool bVsites,t_comm_vsites *vsitecomm,
		    t_commrec *cr,
		    t_graph *graph,t_forcerec *fr);
/* Do conjugate gradients EM! */

extern time_t do_lbfgs(FILE *log,int nfile,t_filenm fnm[],
		       t_inputrec *inputrec,t_topology *top,
		       t_groups *grps,t_state *state,
		       rvec grad[],rvec buf[],t_mdatoms *mdatoms,
		       real ener[],t_fcdata *fcd,
		       t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		       bool bVerbose,bool bVsites,t_comm_vsites *vsitecomm,
		       t_commrec *cr,
		       t_graph *graph,t_forcerec *fr);
/* Do conjugate gradients EM! */


extern time_t do_nm(FILE *log,t_commrec *cr,int nfile,t_filenm fnm[],
		    bool bVerbose,bool bCompact,int stepout,
		    t_inputrec *inputrec,t_groups *grps,
		    t_topology *top,real ener[],t_fcdata *fcd,
		    t_state *state,rvec f[],
		    rvec buf[],t_mdatoms *mdatoms,
		    t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		    t_graph *graph,t_edsamyn *edyn,
		    t_forcerec *fr);
/* Do normal mode analysis */

extern time_t do_tpi(FILE *log,int nfile,t_filenm fnm[], 
		     t_inputrec *inputrec,t_topology *top, 
		     t_groups *grps,
		     t_state *state,rvec f[],rvec buf[],t_mdatoms *mdatoms, 
		     real ener[],t_fcdata *fcd,
		     t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		     bool bVerbose,
		     t_commrec *cr,t_graph *graph,
		     t_forcerec *fr);
/* Do test particle insertion */

/* ROUTINES from runner.c */
extern bool optRerunMDset (int nfile, t_filenm fnm[]);

extern void do_pbc_first(FILE *log,matrix box,t_forcerec *fr,
			 t_graph *graph,rvec x[]);
		     
/* ROUTINES from stat.c */		
extern void global_stat(FILE *log,
			t_commrec *cr,real ener[],
			tensor fvir,tensor svir,rvec mu_tot,
			t_inputrec *inputrec,t_groups *grps,
			t_vcm *vcm,real *terminate);
/* Communicate statistics over cr->mpi_comm_mysim */

void write_traj(t_commrec *cr,
		int fp_trn,bool bX,bool bV,bool bF,
		int fp_xtc,bool bXTC,int xtc_prec,
		t_topology *top_global,
		int step,real t,
		t_state *state_local,t_state *state_global,
		rvec *f_local,rvec *f_global);
/* Routine that writes frames to trn and xtc.
 * Data is collected to the master node only when necessary.
 */

extern int do_per_step(int step,int nstep);
/* Return TRUE if io should be done */

extern int do_any_io(int step, t_inputrec *ir);

/* ROUTINES from sim_util.c */
 
extern void print_time(FILE *out,time_t start,int step,t_inputrec *ir);

extern time_t print_date_and_time(FILE *log,int pid,char *title);

extern void do_force(FILE *log,t_commrec *cr,
		     t_inputrec *inputrec,
		     int step,t_nrnb *nrnb,gmx_wallcycle_t wcycle,
		     t_topology *top,t_groups *grps,
		     matrix box,rvec x[],rvec f[],rvec buf[],
		     t_mdatoms *mdatoms,real ener[],t_fcdata *fcd,
		     real lambda,t_graph *graph,
		     bool bStateChanged,bool bNS,bool bNBFonly,bool bDoForces,
		     t_forcerec *fr, rvec mu_tot,
		     bool bGatherOnly,real t,FILE *field,t_edsamyn *edyn);

extern void sum_lrforces(rvec f[],t_forcerec *fr,int start,int homenr);
		     
extern void calc_virial(FILE *log,int start,int homenr,rvec x[],rvec f[],
			tensor vir_part,tensor vir_el_recip,
			t_graph *graph,matrix box,
			t_nrnb *nrnb,const t_forcerec *fr);
			
extern void nstop_cm(FILE *log,t_commrec *cr,
		     int start,int nr_atoms,real mass[],rvec x[],rvec v[]);

extern void finish_run(FILE *log,t_commrec *cr,char *confout,
		       t_topology *top, t_inputrec *inputrec,
		       t_nrnb nrnb[],gmx_wallcycle_t wcycle,
		       double nodetime,double realtime,int step,
		       bool bWriteStat);

extern void calc_dispcorr(FILE *fplog,t_inputrec *ir,t_forcerec *fr,int step,
			  int natoms,matrix box,real lambda,
			  tensor pres,tensor virial,real ener[]);
     

typedef enum
{
  LIST_SCALARS	=0001,
  LIST_INPUTREC	=0002,
  LIST_TOP	=0004,
  LIST_X	=0010,
  LIST_V	=0020,
  LIST_F	=0040,
  LIST_LOAD	=0100
} t_listitem;

extern void check_nnodes_top(char *fn,t_topology *top);
/* Reset the tpr file to work with one node if necessary */

extern void init_single(FILE *log,
                        t_inputrec *inputrec, char *tpbfile, t_topology *top,
			t_state *state);
     /*
      * Allocates space for the topology (top), the coordinates x, the
      * velocities v, masses mass. Reads the parameters, topology,
      * coordinates and velocities from the file specified in tpbfile
      */

extern void init_parallel(FILE *log,char *tpxfile,t_commrec *cr,
			  t_inputrec *inputrec,t_topology *top,
			  t_state *state,
			  int list);
     /*
      * Loads the data for a simulation from the ring. Parameters, topology
      * coordinates, velocities, and masses are initialised equal to using
      * init_single() in the single processor version. The extra argument
      * f_add is allocated to use for the update of the forces, the load
      * array specifies in which part of the x and f array the subsystems
      * of the other processors are located. Homenr0, homenr1, nparts0 and
      * nparts1 are necessary to calculate the non bonded interaction using
      * the symmetry and thus calculating every force only once. List is a facility
      * for logging (and debugging). One can decide to print none or a set of
      * selected parameters to the file specified by log. Parameters are
      * printed by or-ing the corresponding items from t_listitem. A 0 (zero)
      * specifies that nothing is to be printed on the file. The function
      * returns the number of shifts over the ring to perform to calculate
      * all interactions.
      */

extern void start_time(void);
/* Start timing routines */

extern void update_time(void);
/* Update the timer.This must be done at least every INT_MAX microseconds,
 * or 2400 s, in order to give reliable answers.
 */
 
extern double node_time(void);
/* Return the node time so far in seconds. */

extern void do_shakefirst(FILE *log,real ener[],
			  t_inputrec *inputrec,t_mdatoms *md,
			  t_state *state,rvec buf[],rvec f[],
			  t_graph *graph,t_commrec *cr,t_nrnb *nrnb,
			  t_groups *grps,t_forcerec *fr,t_topology *top,
			  t_edsamyn *edyn,t_pull *pulldata);
			  
extern void dynamic_load_balancing(bool bVerbose,t_commrec *cr,real capacity[],
				   int dimension,t_mdatoms *md,t_topology *top,
				   rvec x[],rvec v[],matrix box);
/* Perform load balancing, i.e. split the particles over processors
 * based on their coordinates in the "dimension" direction.
 */
				   
extern void mdrunner(t_commrec *cr,int nfile,t_filenm fnm[],
		     bool bVerbose,bool bCompact,
		     ivec ddxyz,real rdd,char *loadx,char *loady,char *loadz,
		     int nstepout,
		     t_edsamyn *edyn,int repl_ex_nst,int repl_ex_seed,
		     unsigned long Flags);
/* Driver routine, that calls the different methods */

extern void init_md(t_commrec *cr,t_inputrec *ir,real *t,real *t0,
		    real *lambda,real *lam0,
		    t_nrnb *nrnb,t_topology *top,
		    int nfile,t_filenm fnm[],
		    int *fp_trn,int *fp_xtc,int *fp_ene,
		    FILE **fp_dgdl,FILE **fp_field,
		    t_mdebin **mdebin,t_groups *grps,
		    tensor force_vir,tensor shake_vir,
		    rvec mu_tot,
		    bool *bNEMD,bool *bSimAnn,t_vcm **vcm);
/* Routine in sim_util.c */
     
#endif	/* _mdrun_h */

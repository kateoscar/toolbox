/**************************************************************************
* Matlab entry point - switchyard that allows access to many
*
* Piotr's Image&Video Toolbox      Version NEW
* Copyright 2008 Piotr Dollar.  [pdollar-at-caltech.edu]
* Please email me if you find bugs, or have suggestions or questions!
* Licensed under the Lesser GPL [see external/lgpl.txt]
**************************************************************************/
#include "mex.h"
#include "Matrix.h"
#include "Haar.h"

void checkArgs( char *action, int nlhs, int maxlhs, int nrhs, int minrhs, int maxrhs );

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
	// get action to perform
	if(nrhs==0 || !mxIsChar(prhs[0]) )
		mexErrMsgTxt( "First input argument must be a string." );
	char action[1024]; mxGetString(prhs[0], action, 1024);

	try{
		assert(false);
		if( !strcmp(action,"getPrimitiveTest") ) {
			// simple test - pass primitive to Matlab
			checkArgs(action,nlhs,1,nrhs,1,1);
			int flag = (int) mxGetScalar(prhs[1]); ObjImg X;
			if(flag==0)      { int x=87519651; X.frmPrim("x",&x); }
			else if(flag==1) { int x[5]={1,2,3,4,5}; X.frmPrim("x",x,5); }
			else if(flag==2) { bool x[4]={true,false,true,false}; X.frmPrim("x",x,4); }
			else if(flag==3) { uchar x[7]={-1,1,2,3,4,5,256}; X.frmPrim("x",x,7); }
			else if(flag==4) { double x=1.15415987557; X.frmPrim("x",&x); }
			else if(flag==5) { float x[2]={59.5,7500}; X.frmPrim("x",x,2); }
			else if(flag==6) { char *x="whatev yo"; X.frmPrim("x",x,strlen(x)+1); }
			else mexErrMsgTxt("Invalid flag");
			mxArray *M=X.toMxArray(); X.clear(); X.frmMxArray(M);
			plhs[0] = X.toMxArray();

		} else if( !strcmp(action,"getSavableTest") ) {
			// simple test - pass Savable object to Matlab
			checkArgs(action,nlhs,1,nrhs,1,1);
			int flag = (int) mxGetScalar(prhs[1]); ObjImg X;
			if(flag==0)      { Matrixd x(5,5,0); for(int i=0; i<5; i++) x(i,i)=i; X.frmSavable("x",&x); }
			else if(flag==1) { Haar x; x.createSyst(1,25,25,10,10,0,0); x.finalize(); X.frmSavable("x",&x); }
			else if(flag==2) { Rect x(0,0,10,10); x._wt=.3f; X.frmSavable("x",&x); }
			else if(flag==3) { VecSavable x; X.frmSavable("x",&x); }
			else mexErrMsgTxt("Invalid flag");
			mxArray *M=X.toMxArray(); X.clear(); X.frmMxArray(M);
			plhs[0] = X.toMxArray();

		} else if( !strcmp(action,"transpose") ) {
			// transpose matrix
			checkArgs(action,nlhs,1,nrhs,1,1);
			Matrixd A; A.frmMxArray(prhs[1]);
			A.transpose(); plhs[0]=A.toMxArray();

		} else {
			// action not recognized
			char err[1124]; sprintf(err,"Unkown action: %s.",action); mexErrMsgTxt(err);
		}
	} catch(...) {
		mexErrMsgTxt("some exception occurred.");
	}
}

void checkArgs( char *action, int nlhs, int maxlhs, int nrhs, int minrhs, int maxrhs )
{
	char err[2048]; err[0]='\0'; nrhs=nrhs-1;
	if( nlhs>maxlhs ) sprintf(err,"%s: too MANY outputs (%i), at most %i expected.",action,nlhs,maxlhs);
	if( nrhs<minrhs ) sprintf(err,"%s: too FEW inputs (%i), at least %i expected.",action,nrhs,minrhs);
	if( nrhs>maxrhs ) sprintf(err,"%s: too MANY inputs (%i), at most %i expected.",action,nrhs,maxrhs);
	if( strlen(err)>0 ) mexErrMsgTxt(err);
}

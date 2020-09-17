#ifndef ToolFunctions_hpp
#define ToolFunctions_hpp



void CoutTheFitFuncResults(TF1 * func_fp)
{
    Int_t myGetNpar = func_fp->GetNpar();
    Int_t myGetNDF = func_fp->GetNDF();
    Double_t myGetChiSquare = func_fp->GetChisquare();
    const Double_t *myGetParameters = func_fp->GetParameters();
    const Double_t *myGetParErrors = func_fp->GetParErrors();
    
    cout << endl;
    cout << endl << "**********************************************************************" << endl;
    cout << func_fp->GetName() << endl;
    // cout << func_fp->GetTitle() << endl;
    cout << myGetChiSquare << "    " << myGetNDF << "     ";
    for(int i = 0; i < myGetNpar; i ++)
    {
        cout << *(myGetParameters+i) << "    " ;
    }
    cout << endl;
    cout << 0 << "    " << 0 << "    " ;
    for(int i = 0; i < myGetNpar; i ++)
    {
        cout << *(myGetParErrors+i) << "    ";
    }

    cout << endl << "**********************************************************************" << endl;
    cout << endl;
    // func_fp->Gets
}

void CoutTheFitFuncResultstoFile(TF1 * func_fp, ofstream & outFile)
{
    Int_t myGetNpar = func_fp->GetNpar();
    Int_t myGetNDF = func_fp->GetNDF();
    Double_t myGetChiSquare = func_fp->GetChisquare();
    const Double_t *myGetParameters = func_fp->GetParameters();
    const Double_t *myGetParErrors = func_fp->GetParErrors();
    
    outFile << endl;
    for(int i = 0; i < myGetNpar; i ++)
    {
        outFile << *(myGetParameters+i) << "    " ;
    }
    outFile << endl;
    outFile << 0 << "    " << 0 << "    " ;//chi2 和 NDF的误差
    for(int i = 0; i < myGetNpar; i ++)
    {
        outFile << *(myGetParErrors+i) << "    ";
    }
    outFile << endl;
}

void CoutTheTranslate_wtoN(TF1 * myfunc)
{        
    Double_t N = myfunc->GetParameter(0);
    Double_t tauA1 = myfunc->GetParameter(1);
    Double_t tauA2 = myfunc->GetParameter(2);
    Double_t tauB = myfunc->GetParameter(3);
    Double_t mean = myfunc->GetParameter(4);
    Double_t sigma = myfunc->GetParameter(5);
    Double_t w1= myfunc->GetParameter(6);
    Double_t w = myfunc->GetParameter(7);
    Double_t N_delta =myfunc->GetParameter(8);

    Double_t N_A1 = N*(  w*w1*tauA1/(tauA1-tauB) + (1-w)   );
    Double_t N_A2 = N*(  w*(1-w1)*tauA2/(tauA2-tauB) + (1-w)  );
    Double_t N_B = N*(  w*w1*(-tauB)/(tauA1-tauB) +  w*(1-w1)*(-tauB)/(tauA2-tauB) );

    cout << "N_A1  = " << N_A1 << endl; 
    cout << "N_A2  = " << N_A2 << endl; 
    cout << "N_B  = " << N_B << endl; 

}





#endif
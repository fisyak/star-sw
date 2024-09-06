/* Draw projection of THnSparse from StiPull 
   root.exe All.PullsH.root
 */
void DrawPulls(const Char_t *type = "P") {// type = "" +> Global
  const Char_t *NameV[5] = {  "Z", "tanP", "tanL", "AdcL", "dX"};
  //            YZ IO
  THnSparse *pulls[2][2] = {0};
  pulls[0][0] = (THnSparse *) gDirectory->Get(Form("pull%sYI",type));
  pulls[0][1] = (THnSparse *) gDirectory->Get(Form("pull%sYO",type));
  pulls[1][0] = (THnSparse *) gDirectory->Get(Form("pull%sZI",type));
  pulls[1][1] = (THnSparse *) gDirectory->Get(Form("pull%sZO",type));
  TCanvas *c1 = new TCanvas("cYZ","cYZ", 1200, 1800);
  const Char_t *Var[2] = {"y","z"};
  c1->Divide(2,4);
  TObjArray *arr = new TObjArray(4);
  for (Int_t iyz = 0; iyz < 2; iyz++) {
    for (Int_t iv  = 0; iv < 4;  iv++) {
      TLegend *l = new TLegend(0.4,0.7,0.6,0.90);
      for (Int_t io = 0; io <2; io++) {
	if (! pulls[iyz][io]) continue;
	TH2 *h2 = (TH2 *) pulls[iyz][io]->Projection(4, iv);
	if (! h2) continue;
	c1->cd(2*iv+iyz+1);
	TString Title(Form("pull #sigma_{%s} versus %s",Var[iyz], NameV[iv]));
	h2->FitSlicesY(0, 0, -1, 0, "QNRg3s", arr);
	TH1 *mu = (TH1 *) (*arr)[1];
	TH1 *sigma = (TH1 *) (*arr)[2]; sigma->SetMarkerStyle(21);
	sigma->SetTitle(Title);
	sigma->SetXTitle(NameV[iv]);
	sigma->SetMarkerColor(io+1);
	if (! io) {sigma->Draw(); l->AddEntry(sigma,"Inner");}
	else      {sigma->Draw("sames"); l->AddEntry(sigma,"Outer");}
      }
      l->Draw();
      c1->Update();
    }
  }
}

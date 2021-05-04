
void DrawHist(){
TFile *_file1 = TFile::Open ("C:/Users/Alexandr/Documents/Work_with_geant4/GMINUS2/silicon/GammaDet_build/RelWithDebInfo/gamma_1_1_mev_10particle_100000event_pureSi_defaultcut.root");
TFile *_file2 = TFile::Open ("C:/Users/Alexandr/Documents/Work_with_geant4/GMINUS2/silicon/GammaDet_build/RelWithDebInfo/gamma_1_3_mev_10particle_100000event_pureSi_defaultcut.root");



TH1F *h11=(TH1F*)_file1->Get("h4")->Clone("h11");
TH1F *h12=(TH1F*)_file2->Get("h4")->Clone("h12");


/*
for(int i=1;i<=h8->GetNbinsX();i++){
h8->SetBinContent(i,float(h8->GetBinContent(i))/h8->GetBinWidth(i));	
h8->SetBinError(i,float(h8->GetBinError(i))/h8->GetBinWidth(i));
}
for(int i=1;i<=h7->GetNbinsX();i++){
h7->SetBinContent(i,float(h7->GetBinContent(i))/(h7->GetBinWidth(i)));	
h7->SetBinError(i,float(h7->GetBinError(i))/(h7->GetBinWidth(i)));
}
for(int i=1;i<=h3->GetNbinsX();i++){
h3->SetBinContent(i,float(h3->GetBinContent(i))/h3->GetBinWidth(i));	
h3->SetBinError(i,float(h3->GetBinError(i))/h3->GetBinWidth(i));
}
for(int i=1;i<=h11->GetNbinsX();i++){
h11->SetBinContent(i,float(h11->GetBinContent(i))/h11->GetBinWidth(i));	
h11->SetBinError(i,float(h11->GetBinError(i))/h11->GetBinWidth(i));
}
for(int i=1;i<=h12->GetNbinsX();i++){
h12->SetBinContent(i,float(h12->GetBinContent(i))/h12->GetBinWidth(i));	
h12->SetBinError(i,float(h12->GetBinError(i))/h12->GetBinWidth(i));
}
for(int i=1;i<=h14->GetNbinsX();i++){
h14->SetBinContent(i,float(h14->GetBinContent(i))/h14->GetBinWidth(i));	
h14->SetBinError(i,float(h14->GetBinError(i))/h14->GetBinWidth(i));
}
for(int i=1;i<=h13->GetNbinsX();i++){
h13->SetBinContent(i,float(h13->GetBinContent(i))/h13->GetBinWidth(i));	
h13->SetBinError(i,float(h13->GetBinError(i))/h13->GetBinWidth(i));
}
for(int i=1;i<=h15->GetNbinsX();i++){
h15->SetBinContent(i,float(h15->GetBinContent(i))/h15->GetBinWidth(i));	
h15->SetBinError(i,float(h15->GetBinError(i))/h15->GetBinWidth(i));
}
for(int i=1;i<=h16->GetNbinsX();i++){
h16->SetBinContent(i,float(h16->GetBinContent(i))/h16->GetBinWidth(i));	
h16->SetBinError(i,float(h16->GetBinError(i))/h16->GetBinWidth(i));
}*/

h12->SetLineColor(kGreen);
h12->SetMarkerStyle(20);
h12->SetMarkerSize(0.8);
h12->SetMarkerColor(kGreen);

h11->SetLineColor(kRed);
h11->SetMarkerStyle(20);
h11->SetMarkerSize(0.8);
h11->SetMarkerColor(kRed);
h11->SetTitle("Comparison of absorbed photon energy in straws");

h11->GetXaxis()->SetTitle("XTR energy [keV]");//#Theta [rad]   XTR energy [keV]
h11->GetYaxis()->SetTitle("Entries/NumberOfEvents");//
//h18->GetXaxis()->SetRangeUser(1., 50.);
//h18->GetYaxis()->SetRangeUser(0, 0.031);


TCanvas *c_inc_gener=new TCanvas("c_inc_gener","c_inc_gener",800,600);
h11->Draw("");
h12->Draw("same");

}
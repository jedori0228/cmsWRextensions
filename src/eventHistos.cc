#include "ExoAnalysis/cmsWRextensions/interface/eventHistos.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH2D.h"
//C++ CLASSES
#include <iostream>
////LOCAL CLASSES
#include "ExoAnalysis/cmsWRextensions/interface/eventBits.h"
#include "ExoAnalysis/cmsWRextensions/interface/tools.h"





eventHistos::eventHistos () {}




void eventHistos::book(TFileDirectory histoFolder, uint16_t flavor, std::string tag, bool FSB) {

  //CREATED FOLDER IN HISTO
  m_flavor = flavor;
  m_histoFolder = histoFolder;
  m_FSB = FSB;

  std::cout<<"TAGGING EVENTS WITH: "  <<tag<<std::endl;
  m_metaData = m_histoFolder.make<TH1D>("metadata", "events metadata", 10, 0.0, 10);
  m_metaData->GetXaxis()->SetBinLabel(1, tag.c_str());

  std::cout<<"TAG SET TO: "<<m_metaData->GetXaxis()->GetBinLabel(1)<<std::endl;

  if (m_flavor != 4) {
  //MAKE GEN PLOTS
    std::cout << "HERE WE CONSTRUCT THE PLOTS" << std::endl;
    m_eventsWeight = m_histoFolder.make<TH1D>("eventsWeight","number of events weighted", 1, 0.0, 1);



    m_nLeptons       = m_histoFolder.make<TH1D>("nLeptons"     , "; # Leptons; Events per #"     ,                                                       10, -.5, 9.5);
    m_nMuons         = m_histoFolder.make<TH1D>("nMuons"       , "; # Muons; Events per #"       ,                                                       10, -.5, 9.5);
    m_nTaus          = m_histoFolder.make<TH1D>("nTaus"        , "; # Taus; Events per #"        ,                                                       10, -.5, 9.5);
    m_nElectrons     = m_histoFolder.make<TH1D>("nElectrons"   , "; # Electrons; Events per #"   ,                                                       10, -.5, 9.5);
    m_nLightPartons  = m_histoFolder.make<TH1D>("nLightPartons", "; # LightPartons; Events per #",                                                       10, -.5, 9.5);
    m_nTops          = m_histoFolder.make<TH1D>("nTops"        , "; # Tops; Events per #"        ,                                                       10, -.5, 9.5);
    m_nBs            = m_histoFolder.make<TH1D>("nBs"          , "; # Bs; Events per #"          ,                                                       10, -.5, 9.5);
    m_nPartons       = m_histoFolder.make<TH1D>("nPartons"     , "; # Partons; Events per #"     ,                                                       10, -.5, 9.5);
                                                                                     
    m_eventFlavor    = m_histoFolder.make<TH1D>("eventFlavor"       , "; Event Flavor; # Events with flavor"       ,                                                       10, -.5, 9.5);


    m_cutProgress       = m_histoFolder.make<TH1D>("cutProgress"     , "; # Cut Progress; Events passing cut level"     ,                                                       10, -.5, 9.5);
    m_FSBcutProgress    = m_histoFolder.make<TH1D>("FSBcutProgress"  , "; # Cut Progress in flavour sideband; Events passing cut level"     ,                                   10, -.5, 9.5);
    
    m_parton1Et =                       m_histoFolder.make<TH1D>("parton1Et", "Parton 1 Et;Et (GeV); ",                         80, 0.0, 4000);
    m_parton2Et =                       m_histoFolder.make<TH1D>("parton2Et", "Parton 2 Et;Et (GeV); ",                         80, 0.0, 4000);
    m_muon1Et =                         m_histoFolder.make<TH1D>("muon1Et", "Muon 1 Et;Et (GeV); ",                             80, 0.0, 4000);
    m_muon2Et =                         m_histoFolder.make<TH1D>("muon2Et", "Muon 2 Et;Et (GeV); ",                             80, 0.0, 4000);

    m_parton1Eta =                      m_histoFolder.make<TH1D>("parton1Eta", "Parton 1 Eta;Eta;",                        80, -4.0, 4.0);
    m_parton2Eta =                      m_histoFolder.make<TH1D>("parton2Eta", "Parton 2 Eta;Eta;",                        80, -4.0, 4.0);
    m_muon1Eta =                        m_histoFolder.make<TH1D>("muon1Eta", "Muon 1 eta;Eta;",                            80, -4.0, 4.0);
    m_muon2Eta =                        m_histoFolder.make<TH1D>("muon2Eta", "Muon 2 eta;Eta;",                            80, -4.0, 4.0);
    m_firstPartonJetEta     =           m_histoFolder.make<TH1D>("firstPartonJetEta", "Jet 1 Eta;Eta;",                    80, -4.0, 4.0);
    m_secondPartonJetEta    =           m_histoFolder.make<TH1D>("secondPartonJetEta", "Jet 2 Eta;Eta;",                   80, -4.0, 4.0);
    m_firstPartonAK8JetEta  =           m_histoFolder.make<TH1D>("firstPartonAK8JetEta", "AK8Jet 1 Eta;Eta;",              80, -4.0, 4.0); 
    m_secondPartonAK8JetEta =           m_histoFolder.make<TH1D>("secondPartonAK8JetEta", "AK8Jet 2 Eta;Eta;",             80, -4.0, 4.0);

    m_parton1Phi             =          m_histoFolder.make<TH1D>("parton1Phi", "Parton 1 Phi;Phi (rad);",                        80, -4.0, 4.0);        
    m_parton2Phi             =          m_histoFolder.make<TH1D>("parton2Phi", "Parton 2 Phi;Phi (rad);",                        80, -4.0, 4.0);       
    m_muon1Phi               =          m_histoFolder.make<TH1D>("muon1Phi", "Muon 1 Phi;Phi (rad);",                            80, -4.0, 4.0);        
    m_muon2Phi               =          m_histoFolder.make<TH1D>("muon2Phi", "Muon 2 Phi;Phi (rad);",                            80, -4.0, 4.0);        
    m_firstPartonJetPhi      =          m_histoFolder.make<TH1D>("firstPartonJetPhi", "Jet 1 Phi;Phi (rad);",                    80, -4.0, 4.0);     
    m_secondPartonJetPhi     =          m_histoFolder.make<TH1D>("secondPartonJetPhi", "Jet 2 Phi;Phi (rad);",                   80, -4.0, 4.0);       
    m_firstPartonAK8JetPhi   =          m_histoFolder.make<TH1D>("firstPartonAK8JetPhi", "AK8Jet 1 Phi;Phi (rad);",              80, -4.0, 4.0);        
    m_secondPartonAK8JetPhi  =          m_histoFolder.make<TH1D>("secondPartonAK8JetPhi", "AK8Jet 1 Phi;Phi (rad);",             80, -4.0, 4.0);           

    m_dRparton1parton2 =                m_histoFolder.make<TH1D>("dRparton1parton2", "deltaR between partons;delta R;",                       120, 0.0, 12.0);
    m_dRmuon1muon2 =                    m_histoFolder.make<TH1D>("dRmuon1muon2", "deltaR between muons;delta R;",                             120, 0.0, 12.0);
    m_dRparton1muon2 =                  m_histoFolder.make<TH1D>("dRparton1muon2", "deltaR between parton1 and muon2;delta R;",               120, 0.0, 12.0);
    m_dRparton1muon1 =                  m_histoFolder.make<TH1D>("dRparton1muon1", "deltaR between parton1 and muon1;delta R;",               120, 0.0, 12.0);
    m_dRparton2muon2 =                  m_histoFolder.make<TH1D>("dRparton2muon2", "deltaR between parton2 and muon2;delta R;",               120, 0.0, 12.0);
    m_dRparton2muon1 =                  m_histoFolder.make<TH1D>("dRparton2muon1", "deltaR between parton2 and muon1;delta R;",               120, 0.0, 12.0);
    m_dRparton1jet =                    m_histoFolder.make<TH1D>("dRparton1jet", "deltaR between parton1 and closest jet;delta R;",            40, 0.0,  0.4);
    m_dRparton2jet =                    m_histoFolder.make<TH1D>("dRparton2jet", "deltaR between parton2 and closest jet;delta R;",            40, 0.0,  0.4);
    m_dRparton1AK8jet =                 m_histoFolder.make<TH1D>("dRparton1AK8jet", "deltaR between parton1 and closest AK8 jet;delta R;",     40, 0.0,  0.8);
    m_dRparton2AK8jet =                 m_histoFolder.make<TH1D>("dRparton2AK8jet", "deltaR between parton2 and closest AK8 jet;delta R;",     40, 0.0,  0.8);

    m_firstPartonJetEt =                m_histoFolder.make<TH1D>("firstPartonJetEt", " Jet Et for Leading Parton;Et (GeV);",                      80,0.0,4000);
    m_secondPartonJetEt =               m_histoFolder.make<TH1D>("secondPartonJetEt"," Jet Et for Subleading Parton;Et (GeV);",                   80,0.0,4000);
    m_firstPartonJetEtHadronic =        m_histoFolder.make<TH1D>("firstPartonJetEtHadronic", "Hadronic Jet Et for Leading Parton;Et (GeV);",      80,0.0,4000);
    m_secondPartonJetEtHadronic =       m_histoFolder.make<TH1D>("secondPartonJetEtHadronic","Hadronic Jet Et for Subleading Parton;Et (GeV);",   80,0.0,4000);
    m_firstPartonJetEtEM =              m_histoFolder.make<TH1D>("firstPartonJetEtEM", "EM Jet Et for Leading Parton;Et (GeV);",                  80,0.0,4000);
    m_secondPartonJetEtEM =             m_histoFolder.make<TH1D>("secondPartonJetEtEM","EM Jet Et for Subleading Parton;Et (GeV);",               80,0.0,4000);
    m_firstPartonJetEtInvisible =       m_histoFolder.make<TH1D>("firstPartonJetEtInvisible", "Invisible Jet Et for Leading Parton;Et (GeV);",    80,0.0,4000);
    m_secondPartonJetEtInvisible =      m_histoFolder.make<TH1D>("secondPartonJetEtInvisible","Invisible Jet Et for Subleading Parton;Et (GeV);", 80,0.0,4000);

    m_firstPartonAK8JetEt =             m_histoFolder.make<TH1D>("firstPartonAK8JetEt", " AK8Jet Et for Leading Parton;Et (GeV);",                      80,0.0,4000);
    m_secondPartonAK8JetEt =            m_histoFolder.make<TH1D>("secondPartonAK8JetEt"," AK8Jet Et for Subleading Parton;Et (GeV);",                   80,0.0,4000);
    m_firstPartonAK8JetEtHadronic =     m_histoFolder.make<TH1D>("firstPartonAK8JetEtHadronic", "Hadronic AK8Jet Et for Leading Parton;Et (GeV);",      80,0.0,4000);
    m_secondPartonAK8JetEtHadronic =    m_histoFolder.make<TH1D>("secondPartonAK8JetEtHadronic","Hadronic AK8Jet Et for Subleading Parton;Et (GeV);",   80,0.0,4000);
    m_firstPartonAK8JetEtEM =           m_histoFolder.make<TH1D>("firstPartonAK8JetEtEM", "EM AK8Jet Et for Leading Parton;Et (GeV);",                  80,0.0,4000);
    m_secondPartonAK8JetEtEM =          m_histoFolder.make<TH1D>("secondPartonAK8JetEtEM","EM AK8Jet Et for Subleading Parton;Et (GeV);",               80,0.0,4000);
    m_firstPartonAK8JetEtInvisible =    m_histoFolder.make<TH1D>("firstPartonAK8JetEtInvisible", "Invisible AK8Jet Et for Leading Parton;Et (GeV);",    80,0.0,4000);
    m_secondPartonAK8JetEtInvisible =   m_histoFolder.make<TH1D>("secondPartonAK8JetEtInvisible","Invisible AK8Jet Et for Subleading Parton;Et (GeV);", 80,0.0,4000);


    m_leadSubleadingJetsMuonsMass  =    m_histoFolder.make<TH1D>("leadingSubleadingJetsMuonsMass","Four Object Mass of the 2 leading Jets and Muons;Mass (GeV);",      80, 0.0,4000);
    m_leadSubleadingAK8JetsMuonsMass  = m_histoFolder.make<TH1D>("leadingSubleadingAK8JetsMuonsMass","Four Object Mass of the 2 leading AK8Jets and Muons;Mass (GeV);",80, 0.0,4000);
    m_leadSubleadingPartonsMuonsMass  = m_histoFolder.make<TH1D>("leadingSubleadingPartonsMuonsMass","Four Object Mass of the 2 leading Partons and Muons;Mass (GeV);",80, 0.0,4000);
    m_leadAK8JetMuonMass  =           m_histoFolder.make<TH1D>("leadAK8JetMuonMass","2 Object Mass of the leading Jet and Muon;Mass (GeV);"                         ,80, 0.0,4000);
    m_leadAK8JetElectronMass  =           m_histoFolder.make<TH1D>("leadAK8JetElectronMass","2 Object Mass of the leading Jet and Electron;Mass (GeV);"                         ,80, 0.0,4000);

    m_leadSubleadingJetsMuonsPt  =      m_histoFolder.make<TH1D>("leadingSubleadingJetsMuonsPt","Four Object Pt of the 2 leading Jets and Muons; Pt (GeV);",          80, 0.0,4000);
    m_leadSubleadingAK8JetsMuonsPt  =   m_histoFolder.make<TH1D>("leadingSubleadingAK8JetsMuonsPt","Four Object Pt of the 2 leading AK8Jets and Muons; Pt (GeV);",    80, 0.0,4000);
    m_leadSubleadingPartonsMuonsPt  =   m_histoFolder.make<TH1D>("leadingSubleadingPartonsMuonsPt","Four Object Pt of the 2 leading Partons and Muons; Pt (GeV);",    80, 0.0,4000);
    m_leadAK8JetMuonPt  =             m_histoFolder.make<TH1D>("leadAK8JetMuonPt","2 Object Pt of the leading Jet and Muon; Pt (GeV);"                             ,80, 0.0,4000);
    m_leadAK8JetElectronPt  =             m_histoFolder.make<TH1D>("leadAK8JetElectronPt","2 Object Pt of the leading Jet and Electron; Pt (GeV);"                             ,80, 0.0,4000);

    //m_leadSubleadingJetsMuonsEta  =     m_histoFolder.make<TH1D>("leadingSubleadingJetsMuonsEta","Four Object Eta of the 2 leading Jets and Muons",        80, -4.0,4.0);
    //m_leadSubleadingAK8JetsMuonsEta  =  m_histoFolder.make<TH1D>("leadingSubleadingAK8JetsMuonsEta","Four Object Eta of the 2 leading AK8Jets and Muons",  80, -4.0,4.0);
    //m_leadSubleadingPartonsMuonsEta  =  m_histoFolder.make<TH1D>("leadingSubleadingPartonsMuonsEta","Four Object Eta of the 2 leading Partons and Muons",  80, -4.0,4.0);
    //m_leadAK8JetMuonEta  =              m_histoFolder.make<TH1D>("leadAK8JetMuonEta","2 Object Eta of the leading Jet and Muon"                           ,80, -4.0,4.0);

    m_leadAK8JetMuonPhi  =              m_histoFolder.make<TH1D>("leadAK8JetMuonAbsdphi","2 Object delta Phi of the leading Jet and Muon; Phi (rad);"                     ,60, 2.0,3.2);
    m_leadAK8JetElectronPhi  =              m_histoFolder.make<TH1D>("leadAK8JetElectronAbsdphi","2 Object delta Phi of the leading Jet and Electron; Phi (rad);"                     ,60, 2.0,3.2);

    m_leadAK8JetMuonJetMuonEnergyFraction =   m_histoFolder.make<TH1D>("leadAK8JetMuonJetMuonEnergyFraction", "muon energy fraction of ak8jet in the selected jet lepton pair; percent muon energy;", 100, 0.0, 1.0);
    m_leadAK8JetElectronJetMuonEnergyFraction =   m_histoFolder.make<TH1D>("leadAK8JetElectronJetMuonEnergyFraction", "muon energy fraction of ak8jet in the selected jet lepton pair; percent muon energy;", 100, 0.0, 1.0);

    m_electronTrigger =   m_histoFolder.make<TH1D>("electronTrigger", "electron trigger bit; TriggerBit;", 2, -0.5, 1.5);

    m_muonTrigger =   m_histoFolder.make<TH1D>("muonTrigger", "muon trigger bit; TriggerBit;", 2, -0.5, 1.5);

    m_EtPlacementMuon2 =                m_histoFolder.make<TH1D>("EtPlacementMuon2", "Et ranking idx of muon 2;index;",                                 5, -.5, 4.5);
    m_nVertices =                    m_histoFolder.make<TH1D>("nVertices", ";#  Vertices;",                                                       70, -.5, 69.5);
    //m_nJets =                           m_histoFolder.make<TH1D>("nJets", "# of matched jets",                                                   5, -.5, 4.5);
    m_nAK8Jets =                        m_histoFolder.make<TH1D>("nAK8Jets", ";#  AK8Jets;",                                                       10, -.5, 9.5);
    m_nMuonCands =                    m_histoFolder.make<TH1D>("nMuonCands", ";#  Muons;",                                                       10, -.5, 9.5);
    m_nElectronCands =                    m_histoFolder.make<TH1D>("nElectronCands", ";#  Electrons;",                                                       10, -.5, 9.5);
    m_nMuons10 =                        m_histoFolder.make<TH1D>("nMuons10", ";#  Muons above 10 GeV;",                                                       10, -.5, 9.5);
    m_nAK8Jets40 =                      m_histoFolder.make<TH1D>("nAK8Jets40", ";#  AK8Jets above 40 GeV;",                                                       10, -.5, 9.5);
    m_nAdditionalHEEP =                    m_histoFolder.make<TH1D>("nAdditionalHEEP", ";#  Electrons;",                                                       10, -.5, 9.5);

    m_selectedMuonEt  =                 m_histoFolder.make<TH1D>("selectedMuonEt"  ,"Selected Muon Et; High-p_{T} Muon Et (GeV);"  ,80,0.0,4000 ); 
    m_selectedElectronEt  =                 m_histoFolder.make<TH1D>("selectedElectronEt"  ,"Selected Electron Et; Electron Et (GeV);"  ,52,0.0,2000 ); 
    m_selectedJetPt   =                 m_histoFolder.make<TH1D>("selectedJetPt"   ,"Selected Jet Pt; Jet p_{T} (GeV);"   ,40,0.0,2000 );  
    m_selectedMuonPhi =                 m_histoFolder.make<TH1D>("selectedMuonPhi" ,"Selected Muon Phi; High-p_{T} Muon Phi (rad);" ,80,-4.0,4.0 );  
    m_selectedElectronPhi =                 m_histoFolder.make<TH1D>("selectedElectronPhi" ,"Selected Electron Phi; Electron Phi (rad);" ,80,-4.0,4.0 );  
    m_selectedJetPhi  =                 m_histoFolder.make<TH1D>("selectedJetPhi"  ,"Selected Jet Phi; Jet Phi (rad);"  ,80,-4.0,4.0 );   
    m_selectedMuonEta =                 m_histoFolder.make<TH1D>("selectedMuonEta" ,"Selected Muon Eta; High-p_{T} Muon Eta (rad);" ,60,-3.0,3.0 );   
    m_selectedElectronEta =                 m_histoFolder.make<TH1D>("selectedElectronEta" ,"Selected Electron Eta; Electron Eta (rad);" ,60,-3.0,3.0 );   
    m_selectedJetEta  =                 m_histoFolder.make<TH1D>("selectedJetEta"  ,"Selected Jet Eta; Jet Eta (rad);"  ,60,-3.0,3.0 ); 
    m_selectedJetMass  =                 m_histoFolder.make<TH1D>("selectedJetMass"  ,"Selected Jet Mass; Jet softdrop mass (GeV);"  ,60,0.0, 300.0 );
    m_selectedJetTau21  =                 m_histoFolder.make<TH1D>("selectedJetTau21"  ,"Selected Jet Tau21; Jet #tau_{21};"  ,30,0.0, 1.0 );

    m_subleadMuon_selJetdPhi       =    m_histoFolder.make<TH1D>("subleadMuonSelJetdPhi" ,   "Sublead Muon Selected Jet dPhi; Phi (rad);"  ,80,  0.0, 4.0);
    m_subleadMuon_selElectronPhi  =    m_histoFolder.make<TH1D>("subleadMuonSelElectrondPhi", "Sublead Muon Selected Electron dPhi; Phi (rad);" ,80,  0.0, 4.0);
    m_subleadMuon_selElectronMass  =    m_histoFolder.make<TH1D>("subleadMuonSelElectronMass", "Sublead Muon Selected Electron Mass; Mass (GeV);" ,100, 0.0,2000);
    m_subleadMuon_selElectronZMass =    m_histoFolder.make<TH1D>("subleadMuonSelElectronZMass","Sublead Muon Selected Electron Mass; Mass (GeV);" ,100, 0.0,200);
    m_subleadMuon_selElectronPt    =    m_histoFolder.make<TH1D>("subleadMuonSelElectronPt"  , "Sublead Muon Selected Electron Pt; Pt (GeV);"   ,100, 0.0,2000);
    m_subleadMuon_selMuondPhi  =    m_histoFolder.make<TH1D>("subleadMuonSelMuondPhi", "Sublead Muon Selected Muon dPhi; Phi (rad);" ,80,  0.0, 4.0);
    m_subleadMuon_selMuonMass  =    m_histoFolder.make<TH1D>("subleadMuonSelMuonMass", "Sublead Muon Selected Muon Mass; Mass (GeV);" ,100, 0.0,2000);
    m_subleadMuon_selMuonZMass =    m_histoFolder.make<TH1D>("subleadMuonSelMuonZMass","Sublead Muon Selected Muon Mass; Mass (GeV);" ,100, 0.0,200);
    m_subleadMuon_selMuonPt    =    m_histoFolder.make<TH1D>("subleadMuonSelMuonPt"  , "Sublead Muon Selected Muon Pt; Pt (GeV);"   ,100, 0.0,2000);

    m_subleadMuonEt                 =    m_histoFolder.make<TH1D>("subleadMuonEt"           ,  "Sublead Muon Et; Et  (GeV);"              ,100,  0.0, 1000);
    m_subleadMuonEta                =    m_histoFolder.make<TH1D>("subleadMuonEta"          ,  "Sublead Muon Eta; Eta;"                    , 60, -3.0,  3.0);
    m_subleadMuonPhi                =    m_histoFolder.make<TH1D>("subleadMuonPhi"          ,  "Sublead Muon Phi; Phi (rad);"              , 80, -4.0,  4.0);

    m_MET                          =    m_histoFolder.make<TH1D>("MET"                 ,"MET;MET (GeV);# events",                       100, 0.0,2000); //THIS LINE WORKS
    m_MET_selJetdPhi               =    m_histoFolder.make<TH1D>("METselJetdPhi"      ,"MET Selected Jet dPhi; Phi (rad);",      80, 0.0 ,4.0);
    m_MET_selMuondPhi              =    m_histoFolder.make<TH1D>("METselMuondPhi"     ,"MET Selected Muon dPhi; Phi (rad);",     80, 0.0 ,4.0);
    m_MET_selElectrondPhi              =    m_histoFolder.make<TH1D>("METselElectrondPhi"     ,"MET Selected Electron dPhi; Phi (rad);",     80, 0.0 ,4.0);
    m_MET_selJetMass               =    m_histoFolder.make<TH1D>("METselJetMass"      ,"MET Selected Jet Mass; Mass (GeV);",     100,0.0 ,2000);
    m_MET_selMuonMass              =    m_histoFolder.make<TH1D>("METselMuonMass"     ,"MET Selected Muon Mass; Mass (GeV);",    100,0.0 ,2000);
    m_MET_selElectronMass              =    m_histoFolder.make<TH1D>("METselElectronMass"     ,"MET Selected Electron Mass; Mass (GeV);",    100,0.0 ,2000);
    m_MET_selJetPt                 =    m_histoFolder.make<TH1D>("METselJetPt"        ,"MET Selected Jet Pt; Pt (GeV);",       100,0.0 ,2000);
    m_MET_selMuonPt                =    m_histoFolder.make<TH1D>("METselMuonPt"       ,"MET Selected Muon Pt; Pt (GeV);",      100,0.0 ,2000);
    m_MET_selElectronPt                =    m_histoFolder.make<TH1D>("METselElectronPt"       ,"MET Selected Electron Pt; Pt (GeV);",      100,0.0 ,2000);

    m_selectedJetTransMET          =    m_histoFolder.make<TH1D>("selectedJetTransMET",";MET Transverse to Select Jet (GeV);", 100, 0.0, 500);

    m_MuonWeight                   =    m_histoFolder.make<TH1D>("MuonWeight",";Muon Weight", 40, 0.0, 2.0);
    m_PUWeight                     =    m_histoFolder.make<TH1D>("PUWeight",";Pileup Weight", 40, 0.0, 2.0);

    m_HEEP_SF                      =    m_histoFolder.make<TH1D>("HEEP_SF_E",";HEEP Weight All Electron", 40, 0.0, 2.0);
    m_HEEP_SF_E                      =    m_histoFolder.make<TH1D>("HEEP_SF_E",";HEEP Weight Endcap Electron", 40, 0.0, 2.0);
    m_HEEP_SF_B                      =    m_histoFolder.make<TH1D>("HEEP_SF_B",";HEEP Weight Barrel Electron", 40, 0.0, 2.0);
    m_FSBfinalEventWeight_E             =    m_histoFolder.make<TH1D>("FSBfinalEventWeight_E",";final EventWeight FSB Endcap", 40, 0.0, 2.0);
    m_FSBfinalEventWeight_B             =    m_histoFolder.make<TH1D>("FSBfinalEventWeight_B",";final EventWeight FSB Barrel", 40, 0.0, 2.0);

    m_finalEventWeight             =    m_histoFolder.make<TH1D>("finalEventWeight",";finalEventWeight", 40, 0.0, 2.0);

//
//
//  } else if (m_flavor == 2) {
//  //MAKE RECO PLOTS
//
//
//
//
//  } else if (m_flavor == 3) {
//  //MAKE GEN & RECO PLOTS
//
//
//  } else {
//  //NOTHING FOR NOW
//  }
//
  } else if (m_flavor == 4) {
    m_eventsWeight = m_histoFolder.make<TH1D>("eventsWeight","number of events weighted", 1, 0.0, 1);

  }
}
void eventHistos::fill(eventBits& event) {
 // m_outputTag->SetString("blahblah");
  if(m_flavor == 1) fillGen(event);
  else if(m_flavor == 2) {
    fillReco(event);
    fillCutProgress(event);
    fillWeight(event);
  }
  else if(m_flavor == 3) {
    fillGen(event);
    fillReco(event);
    fillCutProgress(event);
    fillWeight(event);
  } else if (m_flavor == 4) {
    fillWeight(event);
  }
  else return;
}

//SPECIFIC 
void eventHistos::fillCutProgress(eventBits& event) {
  double weight = 0.0;
  if(m_FSB == true)
    weight = event.FSBweight;
  else
    weight = event.weight;
  std::cout << "Filling Cut Progress" << std::endl;
  int toFill = event.cutProgress;
  int FSBtoFill = event.FSBcutProgress;
  while (toFill > 0) {
    m_cutProgress->Fill(toFill , weight);
    toFill--;
  }
  while (FSBtoFill > 0) {
    m_FSBcutProgress->Fill(FSBtoFill , weight);
    FSBtoFill--;
  }
}
void eventHistos::fillWeight(eventBits& event) {
  std::cout << "Filling Weights" << std::endl;
  m_eventsWeight->Fill(0.5, event.count);
}
void eventHistos::fillGen(eventBits& event) {
//  std::cout << "Making GEN plots" << std::endl;
//  if(!(event.passesGenCuts())) {
//    std::cout << "ERROR! THIS EVENT SHOULD HAVE FAILED" <<std::endl;
//    return;
//  }
  double weight = 0.0;
  if(m_FSB == true)
    weight = event.FSBweight;
  else
    weight = event.weight;

  std::cout << "Filling Event plots" << std::endl;
  m_nLeptons       ->Fill(event.mynLeptons     , weight) ;
  m_nMuons         ->Fill(event.mynMuons       , weight) ;
  m_nTaus          ->Fill(event.mynTaus        , weight) ;
  m_nElectrons     ->Fill(event.mynElectrons   , weight) ;
  m_nLightPartons  ->Fill(event.mynLightPartons, weight) ;
  m_nTops          ->Fill(event.mynTops        , weight) ;
  m_nBs            ->Fill(event.mynBs          , weight) ;
  m_nPartons       ->Fill(event.mynPartons     , weight) ;

  m_parton1Et->Fill(event.parton1EtVal, weight);
  std::cout << "FILLING 1.2"<<std::endl;
  m_parton2Et->Fill(event.parton2EtVal, weight);
  std::cout << "FILLING 1.3"<<std::endl;
  m_muon1Et->Fill(event.muon1EtVal, weight);
  std::cout << "FILLING 1.4"<<std::endl;
  m_muon2Et->Fill(event.muon2EtVal, weight);
  std::cout << "FILLING 1.5"<<std::endl;
  m_firstPartonJetEt->Fill(event.firstPartonJetEtVal, weight);
  std::cout << "FILLING 1.6"<<std::endl;
  m_secondPartonJetEt->Fill(event.secondPartonJetEtVal, weight);
  std::cout << "FILLING 1.7"<<std::endl;
  m_firstPartonAK8JetEt->Fill(event.firstPartonAK8JetEtVal, weight);
  std::cout << "FILLING 1.8"<<std::endl;
  m_secondPartonAK8JetEt->Fill(event.secondPartonAK8JetEtVal, weight);
  std::cout << "FILLING 1.9"<<std::endl;

  m_parton1Eta->Fill(event.parton1EtaVal, weight);
  m_parton2Eta->Fill(event.parton2EtaVal, weight);
  m_muon1Eta->Fill(event.muon1EtaVal, weight);
  m_muon2Eta->Fill(event.muon2EtaVal, weight);
  m_firstPartonJetEta->Fill(event.firstPartonJetEtaVal, weight);
  m_secondPartonJetEta->Fill(event.secondPartonJetEtaVal, weight);
  m_firstPartonAK8JetEta->Fill(event.firstPartonAK8JetEtaVal, weight);
  m_secondPartonAK8JetEta->Fill(event.secondPartonAK8JetEtaVal, weight);
  std::cout << "FILLING 2"<<std::endl;

  m_parton1Phi->Fill(event.parton1PhiVal, weight);
  m_parton2Phi->Fill(event.parton2PhiVal, weight);
  m_muon1Phi->Fill(event.muon1PhiVal, weight);
  m_muon2Phi->Fill(event.muon2PhiVal, weight);
  m_firstPartonJetPhi->Fill(event.firstPartonJetPhiVal, weight);
  m_secondPartonJetPhi->Fill(event.secondPartonJetPhiVal, weight);
  m_firstPartonAK8JetPhi->Fill(event.firstPartonAK8JetPhiVal, weight);
  m_secondPartonAK8JetPhi->Fill(event.secondPartonAK8JetPhiVal, weight);
  std::cout << "FILLING 3"<<std::endl;

  m_dRparton1parton2->Fill(event.dRparton1parton2Val, weight);
  m_dRmuon1muon2->Fill(event.dRmuon1muon2Val, weight);
  m_dRparton1muon2->Fill(event.dRparton1muon2Val, weight);
  m_dRparton1muon1->Fill(event.dRparton1muon1Val, weight);
  m_dRparton2muon2->Fill(event.dRparton2muon2Val, weight);
  m_dRparton2muon1->Fill(event.dRparton2muon1Val, weight);
  m_dRparton1jet->Fill(event.dRparton1jetVal, weight);
  m_dRparton2jet->Fill(event.dRparton2jetVal, weight);
  m_dRparton1AK8jet->Fill(event.dRparton1AK8jetVal, weight);
  m_dRparton2AK8jet->Fill(event.dRparton2AK8jetVal, weight);
  std::cout << "FILLING 4"<<std::endl;



  m_firstPartonJetEtHadronic->Fill(event.firstPartonJetEtHadronicVal, weight);
  m_secondPartonJetEtHadronic->Fill(event.secondPartonJetEtHadronicVal, weight);
  m_firstPartonJetEtEM->Fill(event.firstPartonJetEtEMVal, weight);
  m_secondPartonJetEtEM->Fill(event.secondPartonJetEtEMVal, weight);
  m_firstPartonJetEtInvisible->Fill(event.firstPartonJetEtInvisibleVal, weight);
  m_secondPartonJetEtInvisible->Fill(event.secondPartonJetEtInvisibleVal, weight);
  std::cout << "FILLING 5"<<std::endl;
  

  m_firstPartonAK8JetEtHadronic->Fill(event.firstPartonAK8JetEtHadronicVal, weight);
  m_secondPartonAK8JetEtHadronic->Fill(event.secondPartonAK8JetEtHadronicVal, weight);
  m_firstPartonAK8JetEtEM->Fill(event.firstPartonAK8JetEtEMVal, weight);
  m_secondPartonAK8JetEtEM->Fill(event.secondPartonAK8JetEtEMVal, weight);
  m_firstPartonAK8JetEtInvisible->Fill(event.firstPartonAK8JetEtInvisibleVal, weight);
  m_secondPartonAK8JetEtInvisible->Fill(event.secondPartonAK8JetEtInvisibleVal, weight);
  std::cout << "FILLING 6"<<std::endl;

  m_leadSubleadingPartonsMuonsMass->Fill(event.leadSubleadingPartonsMuonsMassVal, weight);
  std::cout << "FILLING 7"<<std::endl;

  m_leadSubleadingPartonsMuonsPt->Fill(event.leadSubleadingPartonsMuonsPtVal, weight);
  std::cout << "FILLING 8"<<std::endl;

  //m_leadSubleadingJetsMuonsEta->Fill(event.leadSubleadingJetsMuonsEtaVal, weight);
  //m_leadSubleadingPartonsMuonsEta->Fill(event.leadSubleadingPartonsMuonsEtaVal, weight);
  //m_leadSubleadingAK8JetsMuonsEta->Fill(event.leadSubleadingAK8JetsMuonsEtaVal, weight);
  //m_leadAK8JetMuonEta->Fill(event.leadAK8JetMuonEtaVal, weight);

  std::cout << "FILLING 9"<<std::endl;











}
void eventHistos::fillReco(eventBits& event) {
  double weight = 0.0;
  if(m_FSB == true)
    weight = event.FSBweight;
  else
    weight = event.weight;

  m_leadSubleadingJetsMuonsPt->Fill(event.leadSubleadingJetsMuonsPtVal, weight);
  m_leadSubleadingAK8JetsMuonsPt->Fill(event.leadSubleadingAK8JetsMuonsPtVal, weight);
  m_leadAK8JetMuonPt->Fill(event.leadAK8JetMuonPtVal, weight);
  m_leadAK8JetElectronPt->Fill(event.leadAK8JetElectronPtVal, weight);
  m_leadSubleadingJetsMuonsMass->Fill(event.leadSubleadingJetsMuonsMassVal, weight);
  m_leadSubleadingAK8JetsMuonsMass->Fill(event.leadSubleadingAK8JetsMuonsMassVal, weight);
  m_leadAK8JetMuonMass->Fill(event.leadAK8JetMuonMassVal, weight);
  m_leadAK8JetElectronMass->Fill(event.leadAK8JetElectronMassVal, weight);
  m_subleadMuon_selJetdPhi ->   Fill(event.subleadMuon_selJetdPhi ,weight); 
  m_subleadMuon_selMuondPhi-> Fill(event.subleadMuon_selMuondPhi,weight);
  m_subleadMuon_selMuonMass-> Fill(event.subleadMuon_selMuonMass,weight);
  m_subleadMuon_selMuonZMass->Fill(event.subleadMuon_selMuonMass,weight);
  m_subleadMuon_selMuonPt  -> Fill(event.subleadMuon_selMuonPt  ,weight); 

  m_subleadMuon_selElectronPhi-> Fill(event.subleadMuon_selElectronPhi,weight);
  m_subleadMuon_selElectronMass-> Fill(event.subleadMuon_selElectronMass,weight);
  m_subleadMuon_selElectronZMass->Fill(event.subleadMuon_selElectronMass,weight);
  m_subleadMuon_selElectronPt  -> Fill(event.subleadMuon_selElectronPt  ,weight); 

  m_subleadMuonEt           ->   Fill(event.subleadMuonEt           ,weight); 
  m_subleadMuonEta          ->   Fill(event.subleadMuonEta          ,weight); 
  m_subleadMuonPhi          ->   Fill(event.subleadMuonPhi          ,weight); 
                                                               
  m_MET                    ->Fill(event.MET                    ,weight); 
  m_MET_selJetdPhi         ->Fill(event.MET_selJetdPhi         ,weight); 
  m_MET_selMuondPhi        ->Fill(event.MET_selMuondPhi        ,weight); 
  m_MET_selElectrondPhi        ->Fill(event.MET_selElectrondPhi        ,weight); 
  m_MET_selJetMass         ->Fill(event.MET_selJetMass         ,weight); 
  m_MET_selMuonMass        ->Fill(event.MET_selMuonMass        ,weight); 
  m_MET_selElectronMass        ->Fill(event.MET_selElectronMass        ,weight); 
  m_MET_selJetPt           ->Fill(event.MET_selJetPt           ,weight); 
  m_MET_selMuonPt          ->Fill(event.MET_selMuonPt          ,weight); 
  m_MET_selElectronPt          ->Fill(event.MET_selElectronPt          ,weight); 

  m_selectedJetTransMET    ->Fill(event.selectedJetTransMET    ,weight);

  m_selectedMuonEt  ->Fill(event.selectedMuonEt  ,weight); 
  m_selectedElectronEt  ->Fill(event.selectedElectronEt  ,weight); 
  m_selectedJetPt   ->Fill(event.selectedJetPt   ,weight);  
  m_selectedMuonPhi ->Fill(event.selectedMuonPhi ,weight);  
  m_selectedElectronPhi ->Fill(event.selectedElectronPhi ,weight);  
  m_selectedJetPhi  ->Fill(event.selectedJetPhi  ,weight);   
  m_selectedMuonEta ->Fill(event.selectedMuonEta ,weight);   
  m_selectedElectronEta ->Fill(event.selectedElectronEta ,weight);   
  m_selectedJetEta  ->Fill(event.selectedJetEta  ,weight); 
  m_selectedJetMass->Fill(event.selectedJetMass  , weight);
  m_selectedJetTau21->Fill(event.selectedJetTau21, weight);

  m_EtPlacementMuon2->Fill(event.secondInDecayMuon, weight);
  m_nVertices->Fill(event.nVtx, weight);
  //m_nJets->Fill(event.myGenJets.size(), weight);
  m_nAK8Jets->Fill(event.ak8jetCands, weight);
  m_nMuonCands->Fill(event.muonCands, weight);
  m_nElectronCands->Fill(event.electronCands, weight);
  m_nMuons10->Fill(event.muons10, weight);
  m_nAdditionalHEEP->Fill(event.nAdditionalHEEP, weight);
  m_nAK8Jets40->Fill(event.ak8jets40, weight);
  m_leadAK8JetMuonPhi->Fill(event.leadAK8JetMuonPhiVal, weight);
  m_leadAK8JetElectronPhi->Fill(event.leadAK8JetElectronPhiVal, weight);


  m_leadAK8JetMuonJetMuonEnergyFraction->Fill(event.leadAK8JetMuonJetMuonEnergyFraction, weight);
  m_leadAK8JetElectronJetMuonEnergyFraction->Fill(event.leadAK8JetElectronJetMuonEnergyFraction, weight);

  m_electronTrigger->Fill(event.electronTrigger, weight);
  m_muonTrigger->Fill(event.muonTrigger, weight);

  m_MuonWeight->Fill(event.Muon_LooseID_Weight, weight);
  m_PUWeight->Fill(event.puWeight, weight);

  m_HEEP_SF->Fill(event.HEEP_SF, weight);
  m_HEEP_SF_E->Fill(event.HEEP_SF_E, weight);
  m_HEEP_SF_B->Fill(event.HEEP_SF_B, weight);
  m_FSBfinalEventWeight_E->Fill(event.FSBweight_E, weight);
  m_FSBfinalEventWeight_B->Fill(event.FSBweight_B, weight);

  m_finalEventWeight->Fill(weight, weight);

}

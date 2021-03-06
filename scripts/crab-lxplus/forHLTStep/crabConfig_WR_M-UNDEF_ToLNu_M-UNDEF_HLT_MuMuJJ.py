# CRAB3 config template for cmsWR

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.section_("General")
config.General.requestName = 'WR_M-UNDEF_ToLNu_M-UNDEF_HLT_MuMuJJ' 
config.General.workArea = 'crab_projects' 
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis' 
config.JobType.psetName = 'WR_M-UNDEF_ToLNu_M-UNDEF_HLT_MuMuJJ.py'  

config.section_("Data")
config.Data.inputDataset = 'datasetFromDBS'
config.Data.inputDBS = 'phys03'
config.Data.ignoreLocality = True
config.Data.outputDatasetTag = 'RunIIWinter16_80X_mcRun2_asymptotic_2016_miniAODv2_v1_RAWSIM'  
config.Data.outLFNDirBase = '/store/user/aevans/' 
config.Data.publication = True
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1 
config.Data.totalUnits = -1 

config.section_("Site")
config.Site.storageSite = "T2_CH_CERN"
config.Site.blacklist = ["T3_US_UCR", "T2_US_Vanderbilt", "T2_EE_Estonia", "T3_US_UMiss"] 

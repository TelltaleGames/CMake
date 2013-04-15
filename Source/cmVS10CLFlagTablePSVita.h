static cmVS7FlagTable cmVS10PSVitaFlagTable[] =
{
    
  //Fixed Vita properties
  //Enum Properties
  {"GenerateDebugInformation", "g",
   "Generate Debug Information", "true", 0},

  {"InlineFunctionDebug", "Xinlinedebug=0", "", "false", 0},
  {"InlineFunctionDebug", "Xinlinedebug=1", "", "true", 0},
  
  {"Warnings", "w",
   "Turn Off All Warnings", "TurnOffWarnings", 0},
  {"Warnings", "Xdiag=0",
   "Turn Off All Warnings", "TurnOffWarnings", 0},
  {"Warnings", "Xdiag=1",
   "Level4", "GenerateWarnings", 0},
  {"Warnings", "Xdiag=2",
   "EnableAllWarnings", "WarningsAndRemarks", 0},

  {"OptimizationLevel", "O0",
   "Disabled", "Level0", 0},
  {"OptimizationLevel", "O1",
   "Minimize Size", "Level1", 0},
  {"OptimizationLevel", "O2",
   "Maximize Speed", "Level2", 0},
  {"OptimizationLevel", "O3",
   "Full Optimization", "Level3", 0},

  {"FloatingPointModel", "Xfastmath=0",
   "FastMath", "false", 0},
  {"FloatingPointModel", "Xfastmath=1",
   "FastMath", "true", 0},

  {"PrecompiledHeader", "create_pch",
   "Create", "Create",
   cmVS7FlagTable::UserValueIgnored | cmVS7FlagTable::Continue},
  {"PrecompiledHeader", "-use_pch",
   "Use", "Use",
   cmVS7FlagTable::UserValueIgnored | cmVS7FlagTable::Continue},
  {"PrecompiledHeader", "",
   "Not Using Precompiled Headers", "NotUsing", 0},
   
  {"RuntimeTypeInfo", "Xc-=rtti", "", "false", 0},
  {"RuntimeTypeInfo", "Xc+=rtti", "", "true", 0},
  {"CppExceptions", "Xc-=exceptions", "", "false", 0},
  {"CppExceptions", "Xc+=exceptions", "", "true", 0},
  {"MultiProcessorCompilation", "MP", "", "true", 0 },
  
  {"CompileAs", "",
   "Default", "Default", 0},
  {"CompileAs", "TC",
   "Compile as C Code", "CompileAsC", 0},
  {"CompileAs", "TP",
   "Compile as C++ Code", "CompileAsCpp", 0},

  // Skip [XMLDocumentationFileName] - no command line Switch.
  // Skip [BrowseInformationFile] - no command line Switch.
  // Skip [AdditionalOptions] - no command line Switch.
  {0,0,0,0,0}
};

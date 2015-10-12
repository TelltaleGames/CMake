/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmTarget_h
#define cmTarget_h

#include "cmCustomCommand.h"
#include "cmPropertyMap.h"
#include "cmPolicies.h"
#include "cmListFileCache.h"
#include "cmLinkItem.h"

#include <cmsys/auto_ptr.hxx>
#if defined(CMAKE_BUILD_WITH_CMAKE)
# ifdef CMake_HAVE_CXX11_UNORDERED_MAP
#  include <unordered_map>
# else
#  include <cmsys/hash_map.hxx>
# endif
#endif

#define CM_FOR_EACH_TARGET_POLICY(F) \
  F(CMP0003) \
  F(CMP0004) \
  F(CMP0008) \
  F(CMP0020) \
  F(CMP0021) \
  F(CMP0022) \
  F(CMP0027) \
  F(CMP0038) \
  F(CMP0041) \
  F(CMP0042) \
  F(CMP0046) \
  F(CMP0052) \
  F(CMP0060) \
  F(CMP0063) \
  F(CMP0065)

class cmake;
class cmMakefile;
class cmSourceFile;
class cmGlobalGenerator;
class cmComputeLinkInformation;
class cmListFileBacktrace;
class cmTarget;
class cmGeneratorTarget;
class cmTargetTraceDependencies;

class cmTargetInternals;
class cmTargetInternalPointer
{
public:
  cmTargetInternalPointer();
  cmTargetInternalPointer(cmTargetInternalPointer const& r);
  ~cmTargetInternalPointer();
  cmTargetInternalPointer& operator=(cmTargetInternalPointer const& r);
  cmTargetInternals* operator->() const { return this->Pointer; }
  cmTargetInternals* Get() const { return this->Pointer; }
private:
  cmTargetInternals* Pointer;
};

/** \class cmTarget
 * \brief Represent a library or executable target loaded from a makefile.
 *
 * cmTarget represents a target loaded from
 * a makefile.
 */
class cmTarget
{
public:
  cmTarget();
  enum TargetType { EXECUTABLE, STATIC_LIBRARY,
                    SHARED_LIBRARY, MODULE_LIBRARY,
                    OBJECT_LIBRARY, UTILITY, GLOBAL_TARGET,
                    INTERFACE_LIBRARY,
                    UNKNOWN_LIBRARY};
  static const char* GetTargetTypeName(TargetType targetType);
  enum CustomCommandType { PRE_BUILD, PRE_LINK, POST_BUILD };

  /**
   * Return the type of target.
   */
  TargetType GetType() const
    {
    return this->TargetTypeValue;
    }

  /**
   * Set the target type
   */
  void SetType(TargetType f, const std::string& name);

  void MarkAsImported();

  ///! Set/Get the name of the target
  const std::string& GetName() const {return this->Name;}
  std::string GetExportName() const;

  ///! Set the cmMakefile that owns this target
  void SetMakefile(cmMakefile *mf);
  cmMakefile *GetMakefile() const { return this->Makefile;}

#define DECLARE_TARGET_POLICY(POLICY) \
  cmPolicies::PolicyStatus GetPolicyStatus ## POLICY () const \
    { return this->PolicyMap.Get(cmPolicies::POLICY); }

  CM_FOR_EACH_TARGET_POLICY(DECLARE_TARGET_POLICY)

#undef DECLARE_TARGET_POLICY

  /**
   * Get the list of the custom commands for this target
   */
  std::vector<cmCustomCommand> const &GetPreBuildCommands() const
    {return this->PreBuildCommands;}
  std::vector<cmCustomCommand> const &GetPreLinkCommands() const
    {return this->PreLinkCommands;}
  std::vector<cmCustomCommand> const &GetPostBuildCommands() const
    {return this->PostBuildCommands;}
  void AddPreBuildCommand(cmCustomCommand const &cmd)
    {this->PreBuildCommands.push_back(cmd);}
  void AddPreLinkCommand(cmCustomCommand const &cmd)
    {this->PreLinkCommands.push_back(cmd);}
  void AddPostBuildCommand(cmCustomCommand const &cmd)
    {this->PostBuildCommands.push_back(cmd);}

  /**
   * Add sources to the target.
   */
  void AddSources(std::vector<std::string> const& srcs);
  void AddTracedSources(std::vector<std::string> const& srcs);
  cmSourceFile* AddSourceCMP0049(const std::string& src);
  cmSourceFile* AddSource(const std::string& src);

  enum LinkLibraryType {GENERAL, DEBUG, OPTIMIZED};

  //* how we identify a library, by name and type
  typedef std::pair<std::string, LinkLibraryType> LibraryID;

  typedef std::vector<LibraryID > LinkLibraryVectorType;
  const LinkLibraryVectorType &GetOriginalLinkLibraries() const
    {return this->OriginalLinkLibraries;}

  /** Compute the link type to use for the given configuration.  */
  LinkLibraryType ComputeLinkType(const std::string& config) const;

  /**
   * Clear the dependency information recorded for this target, if any.
   */
  void ClearDependencyInformation(cmMakefile& mf, const std::string& target);

  // Check to see if a library is a framework and treat it different on Mac
  bool NameResolvesToFramework(const std::string& libname) const;
  void AddLinkLibrary(cmMakefile& mf,
                      const std::string& target, const std::string& lib,
                      LinkLibraryType llt);
  enum TLLSignature {
    KeywordTLLSignature,
    PlainTLLSignature
  };
  bool PushTLLCommandTrace(TLLSignature signature,
                           cmListFileContext const& lfc);
  void GetTllSignatureTraces(std::ostringstream &s, TLLSignature sig) const;

  void MergeLinkLibraries( cmMakefile& mf, const std::string& selfname,
                           const LinkLibraryVectorType& libs );

  const std::vector<std::string>& GetLinkDirectories() const;

  void AddLinkDirectory(const std::string& d);

  /**
   * Set the path where this target should be installed. This is relative to
   * INSTALL_PREFIX
   */
  std::string GetInstallPath() const {return this->InstallPath;}
  void SetInstallPath(const char *name) {this->InstallPath = name;}

  /**
   * Set the path where this target (if it has a runtime part) should be
   * installed. This is relative to INSTALL_PREFIX
   */
  std::string GetRuntimeInstallPath() const {return this->RuntimeInstallPath;}
  void SetRuntimeInstallPath(const char *name) {
    this->RuntimeInstallPath = name; }

  /**
   * Get/Set whether there is an install rule for this target.
   */
  bool GetHaveInstallRule() const { return this->HaveInstallRule; }
  void SetHaveInstallRule(bool h) { this->HaveInstallRule = h; }

  /** Add a utility on which this project depends. A utility is an executable
   * name as would be specified to the ADD_EXECUTABLE or UTILITY_SOURCE
   * commands. It is not a full path nor does it have an extension.
   */
  void AddUtility(const std::string& u, cmMakefile *makefile = 0);
  ///! Get the utilities used by this target
  std::set<std::string>const& GetUtilities() const { return this->Utilities; }
  std::set<cmLinkItem>const& GetUtilityItems() const;
  cmListFileBacktrace const* GetUtilityBacktrace(const std::string& u) const;

  /** Finalize the target at the end of the Configure step.  */
  void FinishConfigure();

  ///! Set/Get a property of this target file
  void SetProperty(const std::string& prop, const char *value);
  void AppendProperty(const std::string&  prop, const char* value,
          bool asString=false);
  const char *GetProperty(const std::string& prop) const;
  const char *GetProperty(const std::string& prop, cmMakefile* context) const;
  bool GetPropertyAsBool(const std::string& prop) const;
  void CheckProperty(const std::string& prop, cmMakefile* context) const;

  bool IsImported() const {return this->IsImportedTarget;}

  void GetObjectLibrariesCMP0026(std::vector<cmTarget*>& objlibs) const;

  cmTarget const* FindTargetToLink(std::string const& name) const;

  /** Strip off leading and trailing whitespace from an item named in
      the link dependencies of this target.  */
  std::string CheckCMP0004(std::string const& item) const;

  const char* ImportedGetLocation(const std::string& config) const;

  /** Get the target major and minor version numbers interpreted from
      the VERSION property.  Version 0 is returned if the property is
      not set or cannot be parsed.  */
  void GetTargetVersion(int& major, int& minor) const;

  /** Get the target major, minor, and patch version numbers
      interpreted from the VERSION or SOVERSION property.  Version 0
      is returned if the property is not set or cannot be parsed.  */
  void
  GetTargetVersion(bool soversion, int& major, int& minor, int& patch) const;

  /** Does this target have a GNU implib to convert to MS format?  */
  bool HasImplibGNUtoMS() const;

  /** Convert the given GNU import library name (.dll.a) to a name with a new
      extension (.lib or ${CMAKE_IMPORT_LIBRARY_SUFFIX}).  */
  bool GetImplibGNUtoMS(std::string const& gnuName, std::string& out,
                        const char* newExt = 0) const;

  // Get the properties
  cmPropertyMap &GetProperties() const { return this->Properties; }

  bool GetMappedConfig(std::string const& desired_config,
                       const char** loc,
                       const char** imp,
                       std::string& suffix) const;

  /** Get the macro to define when building sources in this target.
      If no macro should be defined null is returned.  */
  const char* GetExportMacro() const;

  /** Return whether this target is an executable with symbol exports
      enabled.  */
  bool IsExecutableWithExports() const;

  /** Return whether this target may be used to link another target.  */
  bool IsLinkable() const;

  /** Return whether or not the target is for a DLL platform.  */
  bool IsDLLPlatform() const { return this->DLLPlatform; }

  /** Return whether or not the target has a DLL import library.  */
  bool HasImportLibrary() const;

  /** Return whether this target is a shared library Framework on
      Apple.  */
  bool IsFrameworkOnApple() const;

  /** Return whether this target is a CFBundle (plugin) on Apple.  */
  bool IsCFBundleOnApple() const;

  /** Return whether this target is a XCTest on Apple.  */
  bool IsXCTestOnApple() const;

  /** Return whether this target is an executable Bundle on Apple.  */
  bool IsAppBundleOnApple() const;

  /** Return the framework version string.  Undefined if
      IsFrameworkOnApple returns false.  */
  std::string GetFrameworkVersion() const;

  /** Get a backtrace from the creation of the target.  */
  cmListFileBacktrace const& GetBacktrace() const;

  /** Get a build-tree directory in which to place target support files.  */
  std::string GetSupportDirectory() const;

  /** @return whether this target have a well defined output file name. */
  bool HaveWellDefinedOutputFiles() const;

  void InsertInclude(std::string const& entry,
                     cmListFileBacktrace const& bt,
                     bool before = false);
  void InsertCompileOption(std::string const& entry,
                           cmListFileBacktrace const& bt,
                           bool before = false);
  void InsertCompileDefinition(std::string const& entry,
                               cmListFileBacktrace const& bt);

  void AppendBuildInterfaceIncludes();

  std::string GetDebugGeneratorExpressions(const std::string &value,
                                  cmTarget::LinkLibraryType llt) const;

  void AddSystemIncludeDirectories(const std::set<std::string> &incs);
  std::set<std::string> const & GetSystemIncludeDirectories() const
    { return this->SystemIncludeDirectories; }

  bool LinkLanguagePropagatesToDependents() const
  { return this->TargetTypeValue == STATIC_LIBRARY; }

  cmStringRange GetIncludeDirectoriesEntries() const;
  cmBacktraceRange GetIncludeDirectoriesBacktraces() const;

  cmStringRange GetCompileOptionsEntries() const;
  cmBacktraceRange GetCompileOptionsBacktraces() const;

  cmStringRange GetCompileFeaturesEntries() const;
  cmBacktraceRange GetCompileFeaturesBacktraces() const;

  cmStringRange GetCompileDefinitionsEntries() const;
  cmBacktraceRange GetCompileDefinitionsBacktraces() const;

  cmStringRange GetSourceEntries() const;
  cmBacktraceRange GetSourceBacktraces() const;
  cmStringRange GetLinkImplementationEntries() const;
  cmBacktraceRange GetLinkImplementationBacktraces() const;


#if defined(_WIN32) && !defined(__CYGWIN__)
  const LinkLibraryVectorType &GetLinkLibrariesForVS6() const {
  return this->LinkLibrariesForVS6;}
#endif

private:
  bool HandleLocationPropertyPolicy(cmMakefile* context) const;

#if defined(_WIN32) && !defined(__CYGWIN__)
  /**
   * A list of direct dependencies. Use in conjunction with DependencyMap.
   */
  typedef std::vector< LibraryID > DependencyList;

  /**
   * This map holds the dependency graph. map[x] returns a set of
   * direct dependencies of x. Note that the direct depenencies are
   * ordered. This is necessary to handle direct dependencies that
   * themselves have no dependency information.
   */
  typedef std::map< LibraryID, DependencyList > DependencyMap;

  /**
   * Inserts \a dep at the end of the dependency list of \a lib.
   */
  void InsertDependencyForVS6( DependencyMap& depMap,
                               const LibraryID& lib,
                               const LibraryID& dep);

  /*
   * Deletes \a dep from the dependency list of \a lib.
   */
  void DeleteDependencyForVS6( DependencyMap& depMap,
                               const LibraryID& lib,
                               const LibraryID& dep);

  /**
   * Emits the library \a lib and all its dependencies into link_line.
   * \a emitted keeps track of the libraries that have been emitted to
   * avoid duplicates--it is more efficient than searching
   * link_line. \a visited is used detect cycles. Note that \a
   * link_line is in reverse order, in that the dependencies of a
   * library are listed before the library itself.
   */
  void EmitForVS6( const LibraryID lib,
                   const DependencyMap& dep_map,
                   std::set<LibraryID>& emitted,
                   std::set<LibraryID>& visited,
                   DependencyList& link_line);

  /**
   * Finds the dependencies for \a lib and inserts them into \a
   * dep_map.
   */
  void GatherDependenciesForVS6( const cmMakefile& mf,
                                 const LibraryID& lib,
                                 DependencyMap& dep_map);

  void AnalyzeLibDependenciesForVS6( const cmMakefile& mf );
#endif

  const char* GetSuffixVariableInternal(bool implib) const;
  const char* GetPrefixVariableInternal(bool implib) const;

  // Use a makefile variable to set a default for the given property.
  // If the variable is not defined use the given default instead.
  void SetPropertyDefault(const std::string& property,
                          const char* default_value);

  std::string GetFullNameImported(const std::string& config,
                                  bool implib) const;

  std::string ImportedGetFullPath(const std::string& config,
                                  bool implib) const;

private:
  mutable cmPropertyMap Properties;
  std::set<std::string> SystemIncludeDirectories;
  std::set<std::string> LinkDirectoriesEmmitted;
  std::set<std::string> Utilities;
  std::map<std::string, cmListFileBacktrace> UtilityBacktraces;
  cmPolicies::PolicyMap PolicyMap;
  std::string Name;
  std::string InstallPath;
  std::string RuntimeInstallPath;
  mutable std::string ExportMacro;
  std::vector<std::string> LinkDirectories;
  std::vector<cmCustomCommand> PreBuildCommands;
  std::vector<cmCustomCommand> PreLinkCommands;
  std::vector<cmCustomCommand> PostBuildCommands;
  std::vector<std::pair<TLLSignature, cmListFileContext> > TLLCommands;
  LinkLibraryVectorType PrevLinkedLibraries;
  LinkLibraryVectorType OriginalLinkLibraries;
#if defined(_WIN32) && !defined(__CYGWIN__)
  LinkLibraryVectorType LinkLibrariesForVS6;
#endif
  cmMakefile* Makefile;
  cmTargetInternalPointer Internal;
  TargetType TargetTypeValue;
  bool HaveInstallRule;
  bool RecordDependencies;
  bool DLLPlatform;
  bool IsAndroid;
  bool IsApple;
  bool IsImportedTarget;
  bool BuildInterfaceIncludesAppended;
#if defined(_WIN32) && !defined(__CYGWIN__)
  bool LinkLibrariesForVS6Analyzed;
#endif

  // Cache import information from properties for each configuration.
  struct ImportInfo
  {
    ImportInfo(): NoSOName(false), Multiplicity(0) {}
    bool NoSOName;
    int Multiplicity;
    std::string Location;
    std::string SOName;
    std::string ImportLibrary;
    std::string Languages;
    std::string Libraries;
    std::string LibrariesProp;
    std::string SharedDeps;
  };

  ImportInfo const* GetImportInfo(const std::string& config) const;
  void ComputeImportInfo(std::string const& desired_config,
                         ImportInfo& info) const;

  std::string ProcessSourceItemCMP0049(const std::string& s);

  void MaybeInvalidatePropertyCache(const std::string& prop);

  // Internal representation details.
  friend class cmTargetInternals;
  friend class cmGeneratorTarget;
  friend class cmTargetTraceDependencies;

  void ComputeVersionedName(std::string& vName,
                            std::string const& prefix,
                            std::string const& base,
                            std::string const& suffix,
                            std::string const& name,
                            const char* version) const;
};

#ifdef CMAKE_BUILD_WITH_CMAKE
#ifdef CMake_HAVE_CXX11_UNORDERED_MAP
typedef std::unordered_map<std::string, cmTarget> cmTargets;
#else
typedef cmsys::hash_map<std::string, cmTarget> cmTargets;
#endif
#else
typedef std::map<std::string,cmTarget> cmTargets;
#endif

class cmTargetSet: public std::set<std::string> {};
class cmTargetManifest: public std::map<std::string, cmTargetSet> {};

#endif

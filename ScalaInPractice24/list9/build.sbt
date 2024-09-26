val SCALATEST_LIB_VERSION = "3.2.18"

lazy val commonSettings = Seq(
  scalacOptions ++= Seq(
      "-deprecation",          // Emit warning and location for usages of deprecated APIs.
      "-encoding", "utf-8",    // Specify character encoding used by source files.
      "-feature",              // Emit warning and location for usages of features that should be imported explicitly.
      "-unchecked",            // Enable additional warnings where generated code depends on assumptions.
      "-Xlint",                // Enable recommended additional warnings.
      "-Ywarn-unused-import",   // Warn when an import selector is not referenced.
      "-Xfatal-warnings",       // Warnings are fatal.
      "-Yrangepos",             // For scoverage.
    ),
  libraryDependencies += "org.scalactic" %% "scalactic" % SCALATEST_LIB_VERSION,
  libraryDependencies += "org.scalatest" %% "scalatest" % SCALATEST_LIB_VERSION % "test",
  semanticdbEnabled := true,
  semanticdbVersion := scalafixSemanticdb.revision,
  scalafixOnCompile := true,
  scalafmtOnCompile := true,
  coverageEnabled := true,
)

lazy val scoverageSettings = Seq(
  coverageFailOnMinimum := true,
  coverageMinimumBranchPerFile := 70,
)

lazy val Core = (project in file("Core")).settings(commonSettings, scoverageSettings)

lazy val Blackjack = (project in file("Blackjack")).dependsOn(Core).settings(commonSettings, scoverageSettings)

lazy val root = (project in file(".")).aggregate(Blackjack, Core).dependsOn(Blackjack, Core).settings(commonSettings)
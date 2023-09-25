---- MODULE AnalyzerDefinesMain ----
EXTENDS AnalyzerDefines, Naturals


ParsedDataSamples ==
  [{"F1", "F2"} -> [1..3 -> 1..3]]


\* Need to assert that no data is lost
\* after merged
ParsedDataValid(Sample, Sample_) ==
  LET Merged == MergeDatas[Sample,
                           Sample_]
  IN  /\ \A x \in DOMAIN Sample:
           \A y \in DOMAIN Sample[x]:
             \E z \in DOMAIN Merged[x]:
               Sample[x][y] = Merged[x][z]
      /\ \A x \in DOMAIN Sample_:
           \A y \in DOMAIN Sample[x]:
             \E z \in DOMAIN Merged[x]:
               Sample[x][y] = Merged[x][z]

Valid ==
    \A sample \in ParsedDataSamples:
     \A sample_ \in ParsedDataSamples:
      ParsedDataValid(sample, sample_)

====================================

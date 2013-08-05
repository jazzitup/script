if [ $# -ge 2 ]; then
  indir=$1
  outdir=$2
  for i in `cmsLs $indir | grep root | awk '{print $NF}'`; do
    cmsStage $i $outdir
  done
else
  echo "Usage: $0 <inputdir> <ouputdir>"
fi

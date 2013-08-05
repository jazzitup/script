t1=$(cat listDir |wc -l)
echo $t1
for (( i=1 ; i<=$t1 ; i++))
  do		
  dir1=`head -$i listDir | tail -1`
  dir2=`head -$i listDir | tail -1 | replace /pnfs/cmsaf.mit.edu/hibat/cms/users/jazzitup /pnfs/cmsaf.mit.edu/t2bat/cms/store/user/jazzitup`
  echo $dir1 	
  echo $dir2	
#  mkdir $dir2
  ls  $dir1/* | awk -v p1=$dir2 '{ print "dccp " $1 " "p1}' | bash
done


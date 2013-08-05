CurrentDir=$PWD
# $1 = input particle name ,     $2 =  intput filename   $3 = runN     $4 script dir                                                            
for (( i=1 ; i<=26 ; i++))
  do
  condor64.sh run.sh  $i   $CurrentDir 
  sleep 0.2
done


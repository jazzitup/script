grep "filterGoodPhotons" *out | grep "TrigReport     1" | awk '{ print $4 "   " $5}' >& temp.txt

tA=0
tB=0
Max=100
ii=0
while read inputline
  do
  A="$(echo $inputline | awk '{ print $1}')"
  B="$(echo $inputline | awk '{ print $2}')"
  echo "$B out of $A"
  tA=$(( $A + $tA ))
  tB=$(( $B + $tB ))
  ii=$(( $ii + 1 )) 
  if (( $ii == Max ));  then
      break
  fi
done < temp.txt

echo "$tB out of $tA"


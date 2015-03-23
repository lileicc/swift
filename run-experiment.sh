#!/bin/bash
BLOG_HOME=~/workspace/bayesianlogic
SWIFT_HOME=~/workspace/swift
BLOG_MODELS="aircraft-static birthday burglary burglary-multihouse csi grades healthiness helicopter-static hurricane-new mixture-of-gaussian-full poisson-ball simple-aircraft tugwar"

#cd $BLOG_HOME
#sbt/sbt stage
#cd $SWIFT_HOME 
#make compile 
set -x
echo 'Experiment Results on Patmos:' >> experiments_output.csv
for model in $BLOG_MODELS ; do
  cd $BLOG_HOME
  echo running BLOG on $model
  ./blog -n 1000000 -q 1000000 example/$model.blog &> $model.output
  BLOG_TIME=$(grep -oP 'Total elapsed time: \K[[:digit:]]*\.[[:digit:]]*' $model.output)
  cd $SWIFT_HOME
  echo running Swift on $model
  ./swifty.sh $model &> $model.output
  SWIFT_TIME=$(grep -oP 'running time: \K[[:digit:]]*\.[[:digit:]]*' $model.output)  
  sed -i "$ a\ ${model} ${BLOG_TIME} ${SWIFT_TIME}" experiments_output.csv
done

#./swifty.sh aircraft-static1
#./swifty.sh birthday
#./swifty.sh birthday0
#./swifty.sh burglary
#./swifty.sh csi
#./swifty.sh healthiness
#./swifty.sh hurricane
#./swifty.sh poisson-ball
#./swifty.sh simple-aircraft
#./swifty.sh sybil-attack-large
#./swifty.sh sybil-attack-original
#./swifty.sh tugwar

#! /bin/sh

infile=ex1629_version.h
outfile=version

recovery=$1

rm -f $outfile

manuf=`grep EX1629_MANUF_STR $infile | cut -d'"' -f2`
model=`grep EX1629_MODEL_STR $infile | cut -d'"' -f2`

prefix=`grep EX1629_VERSION_PREFIX $infile | cut -d'"' -f2`
major=`grep EX1629_VERSION_MAJOR $infile | cut -d' ' -f3`
minor=`grep EX1629_VERSION_MINOR $infile | cut -d' ' -f3`
build=`grep EX1629_VERSION_BUILD $infile | cut -d' ' -f3`
builddate=`date`

if [ "$recovery" = "RECOVERY" ]
then
	echo "Making recovery image"
	sleep 5
	rec_str="_Recovery"
elif [ -z $recovery ]
then
	echo "Making normal image"
	sleep 5
	rec_str=""
else
	echo "Invalid parameter"
	exit 1
fi

echo "$manuf ${model}${rec_str}" >>$outfile
echo "Firmware release $prefix ${major}.${minor}.${build}" >>$outfile
echo "Built ${builddate}" >>$outfile

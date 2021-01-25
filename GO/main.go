package main

import(
	"fmt"
	"math"
	"sort"
	"os"
	"bufio"
	"log"
	"strings"
	"strconv"
)

type ClassifiedPoint struct{
	position []float64
	classification string
}
type ClassifiedDistance struct{
	distance float64
	classification string
}


// Calculates the Eucledian Distance
// Params:
//	dims: The Dimesions, the Euclid should calculate with
//  p1: Array of float positions (Representing the first multidimensional Point)
//  p2: Array of float positions (Representing the scond multidimensional Point)
// Return:
//  The distance between the 2 multidimensional points
func eukl_distance(dims int,p1 []float64, p2 []float64) float64 {
	temp := 0.0
	for i := 0; i < dims; i++{
		temp += math.Pow(p1[i]-p2[i],2)
	}
	return math.Sqrt(temp)
}

// Classifies a given Point with given TrainData
// Params:
// 	traindata: Array of Classified Points (Initial Dataset)
//  toClassify: Array of float Coordiantes, representing the Point to be Classified
//  k: Count of neighbors that schould be looked at
// Return:
// 	A Sorted Slice of ClassifiedDistances (count of equal Classifications is the probability of that Classification)

func classify(dims int, traindata []ClassifiedPoint, toClassify []float64, k int) []ClassifiedDistance{
	distances :=  make([]ClassifiedDistance,len(traindata))
	for i := 0; i< len(traindata); i++ {
		dist:= eukl_distance(dims, traindata[i].position, toClassify)
		distances[i] = ClassifiedDistance{classification: traindata[i].classification, distance: dist}
	}
	sort.Slice(distances,func(i,j int) bool {
		return distances[i].distance < distances[j].distance
	})
	return distances[:k]
}

// Reads the Iris.csv file
// Params:
//  fileName: Path to the csv file
//  headderRows: How many Rows schould be skipped
// Return:
//  Returns an Array of ClassifiedPoints that were read from the file
func readCsv(fileName string, headderRows int) []ClassifiedPoint {
	file, err := os.Open(fileName)

	if err != nil{
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	points := make([]ClassifiedPoint,0)

	for h := 0; h < headderRows; h++{
		scanner.Scan()
	}

	for scanner.Scan(){
		arr := strings.Split(scanner.Text(), ",")

		if len(arr) != 5 {
			continue;
		}

		pos := make([]float64,4)

		for i := 0; i<4;i++{
			t,err := strconv.ParseFloat(arr[i],64)
			if err != nil{
				log.Fatal(err)
			}

			pos[i] = t
		}

		classification := arr[4]
		points = append(points, ClassifiedPoint{position: pos, classification: classification} )
	}
	return points
}



func main()  {

	//Reading the CSV file into an ClassifiedPoint Array
	points := readCsv("../iris.csv",1)

	//Specify the Point to be Classified
	var toClassify = [...]float64 {5.7,3.0,5.2,1.6}

	//Classify in 4 Dims and k=3
	distances := classify(4,points,toClassify[:],3)

	//Print the result
	for p := range distances {
		fmt.Println(distances[p])
	}
}
/*
 * Daniel Joy, drjoy@cn.edu, 0587254
 */
import java.util.*;
import org.apache.commons.math4.legacy.analysis.integration.*;
import org.apache.commons.math4.legacy.analysis.UnivariateFunction;
import org.apache.commons.numbers.gamma.Gamma;
public class FinalProject {
	public static int indexOf(double[] array, double element) { //helper function to find the index of an element in an array
        for (int i = 0; i < array.length; i++) {
            if (array[i] == element) {
                return i;
            }
        }
        return -1;
    }
	public static double findMax(double[] array) { //helper function to find the maximum of the array
        double max = array[0];
        for (double num : array) {
            if (num > max) {
                max = num;
            }
        }
        return max;
    }
	public static double findMin(double[] array) { //helper function to find the minimum of the array
        double min = array[0];
        for (double num : array) {
            if (num < min) {
                min = num;
            }
        }
        return min;
	}
	public static void printLine(String myString, int myIndex, int start, int stop) { //helper function for filling in probability curves
		char[] myLine = myString.toCharArray();
        int lineStop = Math.min(myIndex, stop); //Either stop at the \ or index
    	for(int i = start; i < lineStop; i++) { //Fill in the curve
    		myLine[i] = '#';
    	}
    	for(int i = 0; i < myLine.length; i++) { //Print out the line like normal
    		System.out.print(myLine[i]);
    	}
    	System.out.println();
	}
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int choice;
		while(true) { //Main menu
			System.out.println("What would you like to do?:");
			System.out.println("1) Evaluate a dataset");
			System.out.println("2) Run an R Command");
			System.out.println("3) Simulate a Sample Mean");
			System.out.println("4) Run a t.test");
			System.out.print("\nPlease enter 1, 2, 3, 4: ");
			choice = input.nextInt();
			input.nextLine();
			
			if(choice == 1) { //Evaluating datasets
				System.out.println("Enter the dataset in any of the following forms:");
				System.out.println("variable = c(1,2,3,4);");
				System.out.println("variable = c(1,2,3,4)");
				System.out.println("(1,2,3,4)");
				System.out.println("1, 2, 3, 4");
				System.out.println("1 2 3 4");
				String myinput = input.nextLine();
				String myinput2;
				
				//Make formatting standard
				if(myinput.contains("c")) { //only the numbers
					myinput2 = myinput.substring(myinput.indexOf('c')+2, myinput.indexOf(')'));
				}
				else if(myinput.contains(")")) { //strip to only the numbers
					myinput2 = myinput.substring(myinput.indexOf("(")+1, myinput.indexOf(')'));
				}
				else { //remove spaces and commas
					myinput2 = myinput.replace(" ", ",");
					myinput2 = myinput2.replace(",,", ",");
				}
				String[] dataset3 = myinput2.split(",");
				
				//Convert to double dataset & sort
				double[] dataset = new double[dataset3.length];
		        for (int x = 0; x < dataset3.length; x++) {
		            dataset[x] = Double.parseDouble(dataset3[x]);
		        }
		        Arrays.sort(dataset);
		        
		        double total = 0; // Calculate mean & median
				for(int x = 0; x < dataset.length; x++) {
					System.out.print(dataset[x] + " ");
					total += dataset[x];
				}
				System.out.println("");
		        double mean = total / dataset.length;
		        double median = dataset[dataset.length / 2];
		        
		        double sum = 0; //Calculate standard deviation
		        for(int x = 0; x < dataset.length; x++) {
		        	sum += Math.pow(dataset[x] - mean, 2);
		        }
		        double sd = Math.sqrt(sum / (dataset.length-1));
		        
		        //Calculate shape
		        System.out.println("\nSHAPE");
		        sum = 0;
		        for(int x = 0; x < dataset.length; x++) {
		        	sum += Math.pow((dataset[x] - mean)/sd, 3);
		        }
		        double skewdness = (dataset.length * sum) / ((dataset.length - 1) * (dataset.length-2) * Math.pow(sd, 3));
		        System.out.println("\tSkewdness: " + skewdness);
		        if(skewdness < -1) {
		        	System.out.println("\tShape: heavily left-skewed");
		        }
		        else if(skewdness < -0.5) {
		        	System.out.println("\tShape: slightly left-skewed");
		        }
		        else if(skewdness < 0.5) {
		        	System.out.println("\tShape: pretty symmetric");
		        }
		        else if(skewdness < 1) {
		        	System.out.println("\tShape: slightly right-skewed");
		        }
		        else {
		        	System.out.println("\tShape: heavily right-skewed");
		        }
		        //Calculate Spreads
		        System.out.println("SPREAD");
		        System.out.println("\tRange: " + (dataset[dataset.length-1] - dataset[0]));
		        System.out.println("\tStandard Deviation: " + String.format("%.2f", sd));
		        System.out.println("\tVariance: " + String.format("%.2f", Math.pow(sd, 2)));
		        //Split dataset into 2 datasets
		        double[] dataset1 = new double[dataset.length/2];
		        double[] dataset2 = new double[dataset.length/2];
		        System.arraycopy(dataset, 0, dataset1, 0, dataset.length/2);
		        System.arraycopy(dataset, dataset.length/2, dataset2, 0, dataset.length/2);
		        //Find medians of two smaller datasets to find IQR
		        double IQR1 = dataset1[dataset1.length / 2];
		        double IQR3 = dataset2[dataset2.length / 2];
		        double IQR = IQR3 - IQR1;
		        
		        System.out.println("\tIQR: " + IQR);
		        System.out.println("");
				System.out.println("LOCATION");
				System.out.println("\tMean: " + mean);
				System.out.println("\tMedian: " + median);
				//Calculate modes
				int numUniques = 0;
				double[] uniques = new double[dataset.length];
				for(int x = 0; x < dataset.length; x++) {
					if(!Arrays.asList(uniques).contains(dataset[x])) {
						uniques[numUniques] = dataset[x];
						numUniques += 1;
					}
				}
				double[] popularity = new double[numUniques];
				for(int x = 0; x < dataset.length; x++) {
					popularity[indexOf(uniques, dataset[x])] += 1;
				}
				double max = findMax(popularity);
				int numModes = 0;
				for(int x = 0; x < popularity.length; x++) {
					if(popularity[x] == max) {
						numModes += 1;
					}
				}
				if(numModes > 1) {
					System.out.print("\tModes: ");
				}
				else {
					System.out.print("\tMode: ");
				}
				for(int x = 0; x < dataset.length; x++) {
					if(popularity[x] == max) {
						System.out.print(uniques[x] + " ");
					}
				}
				System.out.println("\n");
			}
			
			else if(choice == 2) { //Simulating an R command
				System.out.println("Which command would you like to run?:");
				System.out.println("1) pnorm");
				System.out.println("2) pt");
				System.out.println("3) pchisq");
				System.out.print("\nPlease enter 1, 2, or 3: ");
				choice = input.nextInt();
				double Finalmean = 0;
				double Finalsd = 0;
				double Finalx = 0;
				double result = 0;
				String distribution = "";
				if(choice == 1) { //Normal Variable
					System.out.println("Pnorm: pnorm(x, mean, sd)");
					System.out.println("Enter x:");
					double x = input.nextDouble();
					System.out.println("Enter mean: ");
					double mean = input.nextDouble();
					System.out.println("Enter sd: ");
					double sd = input.nextDouble();
					distribution = "Normal";
					//Define function for integration
					UnivariateFunction myFunction = new UnivariateFunction() {
			            @Override
			            public double value(double x) {
			                return (1 / (sd * Math.sqrt(2 * Math.PI))) * 
			                        Math.exp(-0.5 * Math.pow((x - mean) / sd, 2));
			            }
			        };
			        //Integrate function, with 1000 rectangles.
			        //Bottom is x-10 because negative infinity caused an error
			        SimpsonIntegrator integrator = new SimpsonIntegrator();
			        result = integrator.integrate(10000, myFunction, (x-10), x);
			        System.out.println("Result: " + String.format("%.3f", result));
			        Finalmean = mean;
			        Finalsd = sd;
			        Finalx = x;
				}
				else if (choice == 2) { //T Variable
					System.out.println("Pt: pt(x, df)");
					System.out.println("Enter x:");
					double x = input.nextDouble();
					System.out.println("Enter number of observations (n): ");
					double n = input.nextDouble();
					distribution = "T";
					//Defining function for integration
					UnivariateFunction myFunction = new UnivariateFunction() {
			            @Override
			            public double value(double x) {
			            	return (Gamma.value((n + 1) / 2.0) / (Math.sqrt(n * Math.PI) * Gamma.value(n / 2.0))) * Math.pow(1 + (x * x) / n, -(n + 1) / 2.0);
						}
			        };
			        //Integrate with 1000 rectangles. x-10 works for bottom range.
			        SimpsonIntegrator integrator = new SimpsonIntegrator();
			        result = integrator.integrate(10000, myFunction, (x-10), x);
			        System.out.println("Result: " + String.format("%.2f", result));
			        
			        Finalmean = 0;
			        Finalsd = Math.sqrt((n-1) / (n-3));
			        Finalx = x;
				}
				else if (choice == 3) { //Chi squared variable
					System.out.println("Pchisq: pchisq(x, n-1)");
					System.out.println("Enter x:");
					double x = input.nextDouble();
					System.out.println("Enter number of observations: ");
					double n = input.nextDouble();
					distribution = "Chisq";
					UnivariateFunction myFunction = new UnivariateFunction() {
			            @Override
			            public double value(double x) {
			            	return (Math.pow(x, (n/2)-1)*Math.exp(-1*x / 2)) / (Math.pow(2, (n/2)) * Gamma.value(n/2));
			            }
			        };
			        SimpsonIntegrator integrator = new SimpsonIntegrator();
			        result = integrator.integrate(10000, myFunction, 0, x);
			        
			        Finalmean = n;
			        Finalsd = Math.sqrt(2*n);
			        Finalx = x;
				}
				int myindex = 0;
		        if(Finalx <= Finalmean) {
		        	//Zscore is how many standard deviations the x is from the mean
		        	int zScore = (int)((Finalmean - Finalx)/Finalsd);
		        	if(distribution == "Normal") {
		        		System.out.println("ZScore: " + zScore);		        		
		        	}
		        	else if (distribution == "T") {
		        		System.out.println("TScore: " + zScore);		        		
		        	}
		        	else {
		        		System.out.println("ChisqScore: " + zScore);
		        	}
		        	//Myindex is where the number will be displayed
		        	myindex = (int)(28 - (52 * (1 - Math.exp(-0.3 * zScore)) / (1 + Math.exp(-0.3 * zScore)) ));
		        	for(int counter = 0; counter < myindex; counter++) {
		        		System.out.print(" ");
		        	}
		        	System.out.print(Finalx);			        	
		        }
		        else {
		        	//Zscore is how many standard deviations the x is from the mean
		        	int zScore = (int)((Finalx - Finalmean)/Finalsd);
		        	if(distribution == "Normal") {
		        		System.out.println("ZScore: " + zScore);		        		
		        	}
		        	else if (distribution == "T") {
		        		System.out.println("TScore: " + zScore);		        		
		        	}
		        	else {
		        		System.out.println("ChisqScore: " + zScore);
		        	}
		        	//Myindex is where the number will be displayed
		        	myindex = (int)(52 * (1 - Math.exp(-0.3 * zScore)) / (1 + Math.exp(-0.3 * zScore)) );
		        	myindex += 28;
		        	for(int counter = 0; counter < 28; counter++) {
		        		System.out.print(" ");
		        	}
		        	for(int counter = 0; counter < myindex-28; counter++) {
		        		System.out.print(" ");
		        	}
		        	System.out.print(Finalx);
		        }
		        System.out.println();
				System.out.println("                        __________                         ");
		        System.out.println("                   ____/    " + Finalmean + "  \\____                   ");
		        //Uses custom function to fill in curve
		        printLine("                __/                    \\__                ", myindex, 19, 39);
		        printLine("              _/                          \\_              ", myindex, 16, 42);
		        printLine("           __/                              \\__           ", myindex, 14, 44);
		        printLine("         _/                                    \\_         ", myindex, 11, 47);
		        printLine("       _/                                        \\_       ", myindex, 9, 49);
		        printLine("    __/                                            \\__    ", myindex, 7, 51);
		        printLine("___/                                                  \\___", myindex, 4, 54);
		        
	        	System.out.println("Or in other words, " + String.format("%.3f", result*100) + "% of the curve is to the left of " + Finalx + "\n");
			}
			else if (choice == 3) { //Simulating a sample mean
				System.out.println("Normal distribution: rnorm(x, mean, sd)");
				System.out.println("Input x (number of samples): ");
				int x = input.nextInt();
				System.out.println("Input mean (center of distribution): ");
				double mean = input.nextDouble();
				System.out.println("Input sd (how wide the distribution is): ");
				double sd = input.nextDouble();
				Random ran = new Random();
				double[] values = new double[x];
				double total = 0;
				System.out.println("Your generated values are:");
				//Generates x number of samples
				for(int i = 0; i < x; i++) {
					//Scale up values from N(0, 1) to defined normal curve
					values[i] = ran.nextGaussian()*sd + mean;
					total += values[i];
					System.out.println(values[i]);
				}
				//Compare expected with actual values to demonstrate how sd shrinks
				System.out.println("\nExpected mean: " + mean);
				System.out.println("Expected sd: " + sd);
				System.out.println("Actual mean: " + total/x);
				//Calculate actual standard deviation
				double total2 = 0;
				for(int i = 0; i < x; i++) {
					total2 += Math.pow((values[i]-(total/x)), 2);
				}
				total2 /= (x-1);
				total2 = Math.sqrt(total2);
				System.out.println("Actual sd: " + total2 + "\n");
			}
			else if (choice == 4){
				System.out.println("t.test(dataset, mu, alternative, conf.level)");
				System.out.println("Enter the dataset in any of the following forms:");
				System.out.println("variable = c(1,2,3,4);");
				System.out.println("variable = c(1,2,3,4)");
				System.out.println("(1,2,3,4)");
				System.out.println("1, 2, 3, 4");
				System.out.println("1 2 3 4");
				String myinput = input.nextLine();
				String myinput2;
				
				//Make formatting standard
				if(myinput.contains("c")) {
					myinput2 = myinput.substring(myinput.indexOf('c')+2, myinput.indexOf(')'));
				}
				else if(myinput.contains(")")) {
					myinput2 = myinput.substring(myinput.indexOf("(")+1, myinput.indexOf(')'));
				}
				else {
					myinput2 = myinput.replace(" ", ",");
					myinput2 = myinput2.replace(",,", ",");
				}
				String[] dataset3 = myinput2.split(",");
				//Convert to double dataset and sort
				double[] dataset = new double[dataset3.length];
		        for (int x = 0; x < dataset3.length; x++) {
		            dataset[x] = Double.parseDouble(dataset3[x]);
		        }
		        Arrays.sort(dataset);
		        int n = dataset.length;
		        
		        //Excepted mean, or what we believe the mean to be
		        System.out.println("Input mu (expected mean value):");
		        double mu = input.nextDouble();
		        //What form does that alternative hypothesis take?
		        System.out.println("Enter the alternative: less, two.sided, greater");
		        String alternative = input.next();
		        //What is the confidence level for it?
		        System.out.println("Enter the confidence level as a decimal (0.01 - 0.99): ");
		        double conflevel = input.nextDouble();
		        
		        double total = 0; // Calculate mean
				for(int x = 0; x < dataset.length; x++) {
					System.out.print(dataset[x] + " ");
					total += dataset[x];
				}
				double sampleMean = total / dataset.length;
				//Calculate standard deviation
				double sum = 0;
		        for(int x = 0; x < dataset.length; x++) {
		        	sum += Math.pow(dataset[x] - sampleMean, 2);
		        }
		        double sd = Math.sqrt(sum / (dataset.length-1));
		        //Calculate step 3 observed t value
		        double t = (sampleMean - mu) / (sd / Math.sqrt(n));
		        
		        //Calculate step 4 Probability
		        UnivariateFunction myFunction = new UnivariateFunction() {
		            @Override
		            public double value(double x) {
		            	return (Gamma.value((n + 1) / 2.0) / (Math.sqrt(n * Math.PI) * Gamma.value(n / 2.0))) * Math.pow(1 + (x * x) / n, -(n + 1) / 2.0);
					}
		        };
		        SimpsonIntegrator integrator = new SimpsonIntegrator();
		        double result = 0;
		        if(alternative.equals("less")) {
			        result = integrator.integrate(10000, myFunction, (t-10), t);
		        }
		        else if (alternative.equals("two.sided")) {
		        	if(t > 0) {
		        		result = 2*integrator.integrate(10000, myFunction, t, t+10);
		        	}
		        	else {
		        		result = 2*integrator.integrate(10000, myFunction, t-10, t);
		        	}
		        }
		        else {
		        	result = integrator.integrate(10000, myFunction, t, t+10);
		        }
		        //Print out output exactly as it would appear in R
		        System.out.println("\n\t\tOne Sample t-test\n");
		        System.out.println("data:");
		        System.out.println("t:" + String.format("%.4f", t) + " df = " + (n-1) + " p-value = " + String.format("%.4f", result));
		        System.out.print("alternative hypothesis: true mean is ");
		        if(alternative.equals("less")) {
		        	System.out.print("less than ");
		        }
		        else if(alternative.equals("two.sided")) {
		        	System.out.print("not equal to ");
		        }
		        else {
		        	System.out.print("greater than ");
		        }
		        System.out.print((int)mu + "\n");
		        System.out.println("sample estimates:\nmean of x\n\t" + sampleMean);
		        System.out.println("");
		        
		        //Print out 5 steps as students would write
		        System.out.print("1) H: u = " + mu + ", K: u");
		        if(alternative.equals("less")) {
		        	System.out.print(" < ");
		        }
		        else if(alternative.equals("two.sided")) {
		        	System.out.print(" != ");
		        }
		        else {
		        	System.out.print(" > ");
		        }
		        System.out.println(mu + ", a = 0.05");
		        System.out.println("2) t = (SampleMean - TrueMean)/(SampleSD / sqrt(n)) ~ t(" + (n-1) + ")");
		        System.out.println("3) tobs = " + String.format("%.4f", t));
		        System.out.println("4) P-value = " + String.format("%.4f", result));
		        if(result < 0.05) {
		        	System.out.println("5) P < a, Reject H");
		        }
		        else {
		        	System.out.println("5) P > a, FTR H");
		        }
		        System.out.println("");
			}
			else {
				break;
			}
		}
		input.close();
	}
}

package base;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;

import weka.classifiers.Classifier;
import weka.core.Attribute;
import weka.core.Instance;
import weka.core.Instances;

public class Resampler {

	//	Variables.
	//
	//++++++++++++++++++++++++++++++++
	Classifier _reference_model = null;
	Instances _training_data = null;
	
	String _path_model_data;
	String _path_training_data;
	String _path_response_data;
	
	/**
	 * The attributes read in from the request.
	 * Each array is a line's worth of attributes for a single instance.
	 */
	ArrayList< double[] > _attributes_in = new ArrayList<>();
	
	/**
	 * The probabilities found via "sample_instance".
	 * Each array is a line's worth of probabilities for a single instance.
	 */
	ArrayList< double[] > _probabilities_out = new ArrayList<>();
	
	String _help_msg = "\n\n" + "--Help--" + "\n" +
						"To run, supply the path from this jar to a dataset request file." + "\n" +
						"The request file should have, for it's first 3 lines the model path, then" + "\n" +
						"the training path, then the response path. The remainder of the file should" + "\n" +
						"be lines of instance attribute values." + "\n" +
						"" + "\n" +
						"The response path is the path this resampler will write it's result to." + "\n" +
						"MAKE SURE THE MODEL AND TRAINING PATHS ARE RELATIVE TO THIS JAR OR ABSOLUTE TO THE SYSTEM!" + "\n" +
						"" + "\n" +
						"Use case example: java -jar runnable.jar ../data/workclass/adult.new_workclass_AM4.request";

	static int ERR_ = -5;
	static final int ERR_NO_REQUEST = ERR_--;
	static final int ERR_NO_MODEL = ERR_--;
	static final int ERR_NO_TRAINING = ERR_--;
	static final int ERR_NO_RESPONSE = ERR_--;
	//++++++++++++++++++++++++++++++++


	//	Helpers (Sampling).
	//
	//++++++++++++++++++++++++++++++++
	public void load_model(String filename) {
		try {
			_reference_model = (Classifier) weka.core.SerializationHelper.read(filename);
		} catch (Exception e) {
			System.out.println( "---Model file not found?---\n" + e.getMessage() );
			System.exit(ERR_NO_MODEL);
		}
	}
	public void load_training(String filename) {
		try {
			_training_data = (Instances) weka.core.SerializationHelper.read(filename);
		} catch (Exception e) {
			System.out.println( "---Training file not found?---\n" + e.getMessage() );
			System.exit(ERR_NO_TRAINING);
		}
	}
	
	/**
	 * Is using .train and .model to sample instances.
	 * This barely uses the .train data.
	 * We want the test instances. All? Some?
	 * @param attributevalues
	 * @return
	 */
	public double[] sample_instance(double[] attributevalues) {
		try {
			Instance newinstance = new Instance(_training_data.firstInstance());
			newinstance.setDataset(_training_data);
			for(int i = 0; i < attributevalues.length; i++)
				newinstance.setValue(i, attributevalues[i]);
			return _reference_model.distributionForInstance(newinstance); //get the probabilities.
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	//++++++++++++++++++++++++++++++++

	//	Input.
	//
	//++++++++++++++++++++++++++++++++
	void read_request( String path ){
		
		//	The file's format should be as follows:
		//	
		//	0:		model path
		//	1:		training path
		//	2:		response path
		//	3:		instance attributes
		//	4:		instance attributes
		//	...
		//	end
		//
		//	Note that the end of the instance attribute line is a categorical value
		//	and should not be considered.
		//
		
		//
		try{
			
			//	Read.
			//
			BufferedReader br = new BufferedReader(new FileReader(path));
			String line;
			line = br.readLine();			

			//	First line is the model path.
			//
			_path_model_data = line;
			line = br.readLine();
			
			//	Second line is the training path.
			//
			_path_training_data = line;
			line = br.readLine();
			
			//	Third line is the response path.
			//
			_path_response_data = line;
			if( !_path_response_data.contains("response") ){
				System.out.println("...no response file found.");
				System.exit(ERR_NO_RESPONSE);
			}
			
			//	The remainder are instance attributes.
			//
			while ((line = br.readLine()) != null) {

				//	Split by comma.
				//
				String[] str_attr = line.split(",");
				
				//	Take all but the last element.
				//
				double[] attr = new double[ str_attr.length - 1 ];
				for(int ii=0; ii<str_attr.length-1; ii++ )
					attr[ii] = Integer.parseInt( str_attr[ii] );
				
				//	Store it.
				//
				_attributes_in.add( attr );
			}
			
			//	Close.
			//
			br.close();
			
		}catch( Exception e ){
			System.out.println( "---Request file not found?---\n" + e.getMessage() );
			System.exit( ERR_NO_REQUEST );
		}
	}
	//++++++++++++++++++++++++++++++++

	//	Output.
	//
	//++++++++++++++++++++++++++++++++
	void write_response(){
		
		//	Write to file each of the lines of instance probabilities we've found.
		//	Write them in the same order in which we read them 
		//	(this should be implicitly done going from 0 to N through our results list).
		//
		
		//
		try{
			
			//	Get our contents.
			//
			String contents = create_response_message();
			
			//	Write.
			//
			BufferedWriter writer = new BufferedWriter( new FileWriter( _path_response_data ) );
			writer.write( contents );
			writer.close();
			
		}catch( Exception e ){
			System.out.println( e.getMessage() );
			System.exit(-6);
		}
	}
	//++++++++++++++++++++++++++++++++

	//	Processing.
	//
	//++++++++++++++++++++++++++++++++
	String create_response_message(){
		
		//
		String result="";
		
		//	Append each instance line of probabilities...
		//
		Iterator<double[]> it = _probabilities_out.iterator();
		while( it.hasNext() ){
			
			//	Create the line.
			//
			String line="";
			
			//	String each of this instance's values.
			//
			double[] p = it.next();
			for( int ii=0; ii<p.length; ii++ )
				line += "" + p[ii] + ",";
			
			//	Remove the last comma.
			//
			line = line.substring(0, line.length() - 1 );
			
			//	Store the line.
			//
			result += line + "\n";
		}
		
		//	Return our result.
		//
		return result;
	}
	
	void check_help( String[] args ){
		
		//
		if( args.length == 0 || args[0].toLowerCase().compareTo("help") == 0 || args[0].toLowerCase().compareTo("h") == 0 ){
			
			//
			System.out.println( _help_msg );
			
			//
			System.exit(0);
		}
	}
	
	public void process( String[] args ){
		
		//
		long t_start = System.nanoTime();
		
		//
		check_help( args );
		
		//
		System.out.println("Resampler begin...");
		
		//
		String path_request = args[0];
		
		//
		read_request(path_request);
		
		//
		load_model(_path_model_data);
		load_training(_path_training_data);
		
		//	Sample each instance's attributes into probabilities.
		//
		Iterator<double[]> attr = _attributes_in.iterator();
		while( attr.hasNext() ){
			double[] instance_attr = attr.next();
			double[] instance_prob = sample_instance(instance_attr);
			_probabilities_out.add( instance_prob );
		}
		
		//
		write_response();
		
		//
		long t_end = System.nanoTime() - t_start;
		double seconds = (double)t_end / 1000000000.0;		
		
		//
		System.out.printf("...Resampler end [elapsed seconds: %f]", seconds );
	}
	//++++++++++++++++++++++++++++++++
	

	//	Main.
	//
	//++++++++++++++++++++++++++++++++
	public static void main(String[] args) { new Resampler().process(args); }
	//++++++++++++++++++++++++++++++++
}

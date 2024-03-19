import java.time.ZonedDateTime;
import java.io.FileNotFoundException;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
//import java.time.temporal.ChronoUnit;

/**
 * Represents a point in space and time, recorded by a GPS sensor.
 *
 * @author Hodo Hasan
 */
public class Track {
  private ArrayList<Point>index;

  public Track(){
    index = new ArrayList<>();
  }

  public Track(String filename) throws IOException {
    this();
    readFile(filename);
  }

  public void readFile(String filename) throws IOException {
    index = new ArrayList<>();
    File file = new File(filename); // this would create a file object for 'filename'
    if(!file.exists()){
        throw new FileNotFoundException(filename + " not found");
      }


    Scanner input = new Scanner(file);
        if(input.hasNextLine())
        input.nextLine(); 


    while (input.hasNextLine()) {
        String line = input.nextLine();// this reads file line by line used lecture 8 to do this 
        String[] commas = line.split(","); // this splits up lines with commas got this from https://www.baeldung.com/string/split
          if(commas.length != 4){
            input.close();
            throw new GPSException("Error - data file does not have fewer than four columns");
          }
          ZonedDateTime time = ZonedDateTime.parse(commas[0]);
          double longitude = Double.parseDouble(commas[1]);
          double latitude = Double.parseDouble(commas[2]);
          double elevation = Double.parseDouble(commas[3]);
          
          Point a = new Point(time, longitude, latitude, elevation);
          add(a);

    }

    input.close();
  }

  public void add(Point a){
    index.add(a);
  }

// Used lecture 5 to assist me with this
public Point get(int p) {
    if(p < 0 || p >= index.size()) { // Correctly calling size() method
        throw new GPSException("Index out of range: " + p);
    }
    return index.get(p); // Correctly using get() method with parentheses
}

public int size() {
    return index.size(); // Correctly calling size() method
}


  public Point lowestPoint() {
    // For the dummy version, this method always returns null.
      if (index.size() == 0) { // inspects if the list 'index' is empty
          throw new GPSException("Error - List is empty or data is in incorret format");
      }
  
      Point lowest = index.get(0); 
      for (Point p : index) {
          if (p.getElevation() < lowest.getElevation()) {
              lowest = p; 
          }
      }
      return lowest; 
  }
  


public Point highestPoint() {
    // For the dummy version, this method always returns null.
    if (index.size() == 0) { // inspects if the list 'index' is empty
          throw new GPSException("Error - List is empty or data is in incorret format");
      }
  
      Point highest = index.get(0); 
      for (Point p : index) {
          if (p.getElevation() > highest.getElevation()) {
              highest = p; 
          }
      }
      return highest; 
  }


public double totalDistance() {
    // For the dummy version, this method always returns 0.
    return 0.0;
}

public double averageSpeed() {
    // For the dummy version, this method always returns 0.
    return 0.0;
}

}



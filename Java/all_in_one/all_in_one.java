// Java Examples to Test Key Concepts

// 1. Basic Syntax and HelloWorld
public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, World!");
    }
}

// 2. Control Structures
class ControlStructures {
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};

        // For loop
        for (int i = 0; i < numbers.length; i++) {
            System.out.println("Number: " + numbers[i]);
        }

        // Enhanced for loop
        for (int num : numbers) {
            System.out.println("Enhanced Loop: " + num);
        }

        // While loop
        int i = 0;
        while (i < numbers.length) {
            System.out.println("While Loop: " + numbers[i]);
            i++;
        }
    }
}

// 3. Classes and Objects
class Animal {
    private String name;

    // Constructor
    public Animal(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}

class TestAnimal {
    public static void main(String[] args) {
        Animal dog = new Animal("Dog");
        System.out.println("Animal: " + dog.getName());

        dog.setName("Cat");
        System.out.println("Updated Animal: " + dog.getName());
    }
}

// 4. Inheritance and Polymorphism
class Vehicle {
    public void move() {
        System.out.println("Vehicle is moving");
    }
}

class Car extends Vehicle {
    @Override
    public void move() {
        System.out.println("Car is driving");
    }
}

class TestVehicle {
    public static void main(String[] args) {
        Vehicle myVehicle = new Car(); // Polymorphism
        myVehicle.move();
    }
}

// 5. Exception Handling
class ExceptionHandling {
    public static void main(String[] args) {
        try {
            int result = 10 / 0; // This will cause an exception
        } catch (ArithmeticException e) {
            System.out.println("Caught an exception: " + e.getMessage());
        } finally {
            System.out.println("This block always executes.");
        }
    }
}

// 6. Collections Framework
import java.util.ArrayList;
import java.util.HashMap;

class CollectionsExample {
    public static void main(String[] args) {
        // ArrayList example
        ArrayList<String> fruits = new ArrayList<>();
        fruits.add("Apple");
        fruits.add("Banana");
        fruits.add("Cherry");

        for (String fruit : fruits) {
            System.out.println("Fruit: " + fruit);
        }

        // HashMap example
        HashMap<String, Integer> map = new HashMap<>();
        map.put("A", 1);
        map.put("B", 2);

        for (String key : map.keySet()) {
            System.out.println("Key: " + key + ", Value: " + map.get(key));
        }
    }
}

// 7. File I/O
import java.io.*;

class FileIOExample {
    public static void main(String[] args) {
        try {
            // Writing to a file
            FileWriter writer = new FileWriter("output.txt");
            writer.write("Hello, File I/O!");
            writer.close();

            // Reading from a file
            BufferedReader reader = new BufferedReader(new FileReader("output.txt"));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

// 8. Multithreading
class MyThread extends Thread {
    public void run() {
        System.out.println("Thread is running");
    }
}

class ThreadExample {
    public static void main(String[] args) {
        MyThread thread = new MyThread();
        thread.start();
    }
}


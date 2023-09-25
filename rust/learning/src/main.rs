use colored::Colorize;
use std::io;
use rand::Rng;


// Don't pay too much attention, maybe there are some jokes in here...
// maybe I've put too much "energy" in that thing.

fn random_number(n0:i32, n1:i32) -> i32{
    rand::thread_rng().gen_range(n0..=n1)
}


fn guess_the_number(){
    let to_guess: u8 = random_number(0,100) as u8;
    let mut n: u32 = 0;

    // if you actually want to play, you can remove this line
    println!("Number to guess is {}", to_guess);

    let mut input = String::from("");
    let mut int_input: u8 = 101; // I'm obliged to do this, or to duplicate some code...
    let mut input_str: &str;
    
    while int_input!= to_guess || input==*""{
        if int_input != 101{
            if to_guess > int_input{
                println!("{}", "It's more than that. (Just saying...)".red());
            }
            else {
                println!("{}", "I think it's less, but you can try whatever you want.".yellow());
            }
        }

        input = String::from("");
        io::stdin().read_line(&mut input).expect("Failed to read line");
        input_str = input.trim();
        int_input = match input_str.parse(){
            Ok(n) => n,
            Err(_) => {
                println!("{}", "You dumb? Try better...".purple());
                continue // ends the loop and restart it
            }
        };

        if int_input>100 {
            println!("{}", "We said that you have to guess between 0 and 100.\n\
            Maybe the next guess will be less disappointing...".blue());
            int_input = 101; // at least it's practicle :D
            continue // ends the loop and restart it
        }
        if n==15{
            println!("{}", "You are at 15 tries, turn on your brain".blue());
        }
        n += 1;
    }
    
    println!("{}", format!("You got it! in {} tries.", n).green().bold());
}



fn examples_for_lists() {
    // init a list - here are some different ways
    let v: Vec<i32> = Vec::new(); 
    println!("{:?}", v);
    let mut v = vec![1,2,3];

    v.push(5);

    // here is how to lazy-ly print a list
    println!("{:?}", v);
}


fn main(){
    guess_the_number();

    println!("\n\nSome example of lists:");
    examples_for_lists(); // it's to not get the warning while compiling.
}



use std::io;
use rand::Rng;


fn random_number(n0: i32, n1:i32) -> i32{
    return rand::thread_rng().gen_range(n0..=n1);
}



fn guess_the_number(){
    let mut l_numbers: Vec<String> = Vec::new();
    for i in 0..10 {
        l_numbers.push(i.to_string());
    }
    l_numbers.push(String::from("-"));
    l_numbers.push(String::from(""));

    let to_guess = random_number(1,100) as u8;
    println!("number to guess: {}", to_guess);

    println!("Enter a number between 0 and 100: ");
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let _ = input.trim();

    // something wrong here ?
    let mut can_be_int = false;
    while !can_be_int{
        can_be_int = true;
        for c in input.chars(){
            if !l_numbers.contains(&String::from(c)){
                can_be_int = false;
                println!("pates");
            }
        }
        if !can_be_int{
            println!("Don't you know what a number is? Try again.");
            io::stdin().read_line(&mut input).expect("Failed to read line");
            let _ = input.trim();
        }
    }

    let input: u8 = input.trim().parse().unwrap();
    
}

fn main() {
    guess_the_number();


    /*
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input);
    
    let my_num: i32 = input.trim().parse()
        .expect("please give me a number!");

    match input.trim().parse::<i32>(){
        Ok(n) => n,
        Err(_) => None,
    };

    println!("{}", my_num*2);
    */ 
}


use std::io;
use rand::Rng;


fn random_number(n0: i32, n1:i32) -> i32{
    return rand::thread_rng().gen_range(n0..=n1);
}



fn guess_the_number(){
    let l_numbers: String = String::from("-1234567890");
    let l_numbers = l_numbers.chars().collect::<Vec<_>>();


    let to_guess = random_number(1,100) as u8;
    println!("number to guess: {}", to_guess);

    println!("Enter a number between 0 and 100: ");
    let mut input = String::new();
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let _ = input.trim().replace("\n","");


    let mut can_be_int = false;
    while !can_be_int{
        can_be_int = true;
        for c in input.chars(){
            if !l_numbers.contains(&c){
                can_be_int = false;
            }
        }
        if !can_be_int{
            println!("Don't you know what a number is? Try again.");
            input = String::from("");
            io::stdin().read_line(&mut input).expect("Failed to read line");
            let _ = input.trim();
        }
    }

    let mut input_int: u8 = input.trim().parse().unwrap();

    while input_int != to_guess{
        println!("Your input: {}", input_int);
        if to_guess > input_int{println!("It's more");}
        else{println!("It's less");}

        input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");
        let _ = input.trim();
        
        can_be_int = false;
        while !can_be_int{
            can_be_int = true;
            println!("{}", input.len());
            if input.len() > 0{
                for c in input.chars(){
                    if !l_numbers.contains(&c){
                        can_be_int = false;
                    }
                }
            } else {
                println!("COUCOU");
                can_be_int = false;}
            if !can_be_int {
                println!("Don't you know what a number is? Try again.");
                input = String::from("");
                io::stdin().read_line(&mut input).expect("Failed to read line");
                let _ = input.trim();
            }
        }
        input_int = input.trim().parse().unwrap();
    }

    println!("GG! you guessed my number!");
}


fn main() {
    guess_the_number();
}


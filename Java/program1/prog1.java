class StringWrapper {
	String value;

	StringWrapper(String s) {
		this.value = s;
	}

	void set(String new_val) {
		this.value = new_val;
	}

	String get() {
		return this.value;
	}
}

public class prog1 {
	static void test(StringWrapper s) {
		s.set("ENC(" + s.get() + ")");
	} 

	public static void main(String[] args) {
		StringWrapper s = new StringWrapper("pasta");
		test(s);
		System.out.println(String.format("Hello World! %s", s.get()));
	}
}


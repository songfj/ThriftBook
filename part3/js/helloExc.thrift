exception bad_msg {
    1: i16    error_code
    2: string msg
}

service hello_error {
	string get_message(1: string name)
	  throws (1: bad_msg bm)
}


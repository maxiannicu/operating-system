void main(){
	char* str = "Hello world";
	char* video_memory = (char*)0xb8000;
	*video_memory = 'x';
}

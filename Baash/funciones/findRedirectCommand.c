//
// Created by tincho on 16/09/17.
//

findRedirectCommand(char*  args,char** in,char** out){
    *in=strstr(args,"<");
    *out=strstr(args,">");
    if(*in!=NULL) {
        if (**in == '<') {
            *(*in+1)='\0';
            **in = '\0';
            *in += 2;
        }
    }
    if(*out!=NULL) {
        if (**out == '>') {
            *(*out-1)='\0';
            **out = '\0';
            *out += 2;
        }
    }
}
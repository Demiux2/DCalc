#include <GL/gl.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <leif/leif.h>

#define WIN_W 400
#define WIN_H 600
#define PADDING 15.0f

#define BUFFER_SIZE 256

#define FONT "/usr/share/fonts/truetype/robotomono/RobotoMono-Bold.ttf"

static void render_panel();
static void render_buttons();

static void resizecb(GLFWwindow* win, int w, int h);

static void exec_op(uint32_t idx);

typedef struct{
    int winw, winh;

    LfInputField input;
    char input_buffer[BUFFER_SIZE];

    LfFont panelfont;
} State;

static const char* icons [20] = {
    "CE",   "C", "()", "/",
    "7",    "8", "9",  "*",
    "4",    "5", "6",  "-",
    "1",    "2", "3",  "+",
    "...",  "0", ".",  "="
};

static State s;

void render_panel(){

    {
		LfUIElementProps props = lf_get_theme().div_props;
		props.corner_radius = 8.0f;
		props.color = (LfColor){80, 80, 80, 255};
		lf_push_style_props(props);
	
		lf_div_begin(((vec2s){PADDING, PADDING}), ((vec2s){s.winw - (PADDING * 2.0f), 125 - (PADDING * 2.0f)}), true);
			lf_pop_style_props();
			lf_text("");
	}

    {
    LfUIElementProps props = lf_get_theme().inputfield_props;
    props.color = LF_NO_COLOR;
    props.border_width = 0.0f;
    props.text_color = LF_WHITE;
    lf_push_style_props(props);
    lf_push_font(&s.panelfont);
    lf_input_text(&s.input);
    lf_pop_font();
    lf_pop_style_props();
    }

	lf_div_end();

    lf_set_ptr_y_absolute(lf_get_ptr_y() + (s.winh / 4.0f) - PADDING);

}

void render_buttons(){

    const float nx = 4, ny = 5;
    const float renderw = s.winw - (PADDING * (nx + 1));
    const float renderh = (s.winh - (WIN_H / 4.0f)) - (PADDING * (ny + 1));
    const float w = renderw / nx, h = renderh / ny;

    float x = PADDING, y = lf_get_ptr_y() + PADDING;
    uint32_t iconidx = 0;

    for(uint32_t iy = 0; iy < ny; iy++){
        for(uint32_t ix = 0; ix < nx; ix++){
            lf_set_ptr_x_absolute(x);
            lf_set_ptr_y_absolute(y);

            LfUIElementProps props = lf_get_theme().button_props;
            props.margin_left   = 0.0f;
            props.margin_right  = 0.0f;
            props.margin_top    = 0.0f;
            props.margin_bottom = 0.0f;
            props.padding = 0.0f;
            props.border_width = 0.0f;
            props.corner_radius = 5.0f;
            props.text_color = LF_WHITE;
            props.color = (LfColor){80, 80, 80, 255};
            lf_push_style_props(props);
            if(lf_button_fixed(icons[iconidx++], w, h) == LF_CLICKED){
                exec_op(iconidx++);
            }
            lf_pop_style_props();

            x += w + PADDING;
        }
    x = PADDING;
    y += h + PADDING;
    }

}

static void resizecb(GLFWwindow* win, int w, int h){
    (void)win;
    s.winw = w;
    s.winh = h;
    lf_resize_display(w, h);
    glViewport(0, 0, w, h);
}

void add_input(char c){

    lf_input_insert_char_idx(&s.input, c, s.input.cursor_index++);

}

void exec_op(uint32_t idx){

    switch(idx){
        case 0:  { break; }
        case 1:  { break; }
        case 2:  { break; }
        case 3:  { add_input("/"); break; }
        case 4:  { add_input("7"); break; }
        case 5:  { add_input("8"); break; }
        case 6:  { add_input("9"); break; }
        case 7:  { add_input("*"); break; }
        case 8:  { add_input("4"); break; }
        case 9:  { add_input("5"); break; }
        case 10: { add_input("6"); break; }
        case 11: { add_input("-"); break; }
        case 12: { add_input("1"); break; }
        case 13: { add_input("2"); break; }
        case 14: { add_input("3"); break; }
        case 15: { add_input("+"); break; }
        case 16: { break; }
        case 17: { add_input("0"); break; }
        case 18: { add_input("."); break; }
        case 19: { add_input("="); break; }
    }

}

int main(){
	
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "test", NULL, NULL);

    s.winw = WIN_W;
    s.winh = WIN_H;

    s.input = (LfInputField){
        .buf = s.input_buffer,
        .width = s.winw - 60.0f,
        .buf_size = BUFFER_SIZE,
        //.advance_height = true,
        .max_chars = BUFFER_SIZE,
        .placeholder = "",
        .selected = true,
};

	glfwMakeContextCurrent(window);

	lf_init_glfw(WIN_W, WIN_H, window);

    glfwSetFramebufferSizeCallback(window, resizecb);

	LfTheme theme = lf_get_theme();
	theme.scrollbar_props.color = (LfColor){160, 160, 160, 255};
	theme.scrollbar_props.corner_radius = 1.5f;
    theme.font = lf_load_font(FONT, 28);
    s.panelfont = lf_load_font(FONT, 38);
	//theme.div_smooth_scroll = false;
	lf_set_theme(theme);

    s.winw = 400.0f;
    s.winh = 600.0f;

	while(!glfwWindowShouldClose(window)){
	
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		lf_begin();

            render_panel();
            render_buttons();
		
		lf_end();

		glfwPollEvents();
		glfwSwapBuffers(window);
	
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

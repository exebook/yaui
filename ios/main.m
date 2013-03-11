/*


int main(int argc, char *argv[])
{
   @autoreleasepool {
       return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
   }
}
*/
/*- (BOOL)textField:(UITextField *)textField 
	shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
	NSString *text = [textField text];
	// NOT BACKSPACE
	if ([string length] || text.length + string.length < 8) {
		return YES;
	} else if (text.length + string.length > 8) {
		return NO;
	} else {
		// DO SOMETHING FOR LENGTH == 8
		return YES;
	}
}*/

/*-(void)scrollViewDidScroll:(UIScrollView *)sender {   
//	printf("%i> scrollViewDidScroll\n", (int)getTickCount());
//	send_js_callback("subview_scroll_end", sender);
	[NSObject cancelPreviousPerformRequestsWithTarget:self];
	[self performSelector:@selector(scrollViewDidEndScrollingAnimation:) withObject:sender afterDelay:0.3]; 
	//...
}

-(void)scrollViewDidEndScrollingAnimation:(UIScrollView *)sender {
	if (ya_set_scroll_pos_lock) {
		printf("ya_set_scroll_pos_lock == true\n");
		return;
	}
//	printf("%i> scrollViewDidEndScrollingAnimation(%i)[%i]\n", (int)getTickCount(), (int)sender, (int)self);
	[NSObject cancelPreviousPerformRequestsWithTarget:self];
	send_js_callback("subview_scroll_end", sender);
}
*/

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface  MYWindow : UIWindow;
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
@end

@interface ViewController : UIViewController<UITextViewDelegate, UITextFieldDelegate>{
   @public
}
@end

@interface AppDelegate : UIResponder <UIApplicationDelegate>
   @property (strong, nonatomic) UIWindow *window;
   @property (strong, nonatomic) ViewController *viewController;
@end

#import <objc/runtime.h>


@interface MYButton : UIButton {
   @public NSString *callback_name; CAGradientLayer *g;
} @end
@interface MYLabel : UILabel { @public NSString *callback_name; } @end
@interface MYInput : UITextField { @public NSString *callback_name; } @end
@interface MYEdit : UITextView { @public NSString *callback_name; int start_distance, start_font_size; } @end

MYWindow *GLOBAL_W;
AppDelegate *GLOBAL_AD;
ViewController *GLOBAL_VC;
NSString *CRET;

char *cp_int(int N) {
	CRET = [[NSNumber numberWithInt:N] stringValue];
	return (char*)[CRET UTF8String];
}
NSString *cp_str(const char *c) {	return [NSString stringWithUTF8String: c];}
int to_int(const char* c) {	return [cp_str(c) intValue];}
double to_dbl(const char* c) {	return [cp_str(c) doubleValue];}
char *cp_ptr(NSObject* O) {	return cp_int((int)O);}

void set_DOCDIR(const char *c);
char * call_cpp(int code, char *command, char *data);

#include <mach/mach.h>
#include <mach/mach_time.h>

uint64_t getTickCount(void) {
    static mach_timebase_info_data_t sTimebaseInfo;
    uint64_t machTime = mach_absolute_time();
    if (sTimebaseInfo.denom == 0 ) { (void) mach_timebase_info(&sTimebaseInfo); }
    uint64_t millis = ((machTime / 1000000) * sTimebaseInfo.numer) / sTimebaseInfo.denom;
    return millis;
}
//#import <Cocoa/Cocoa.h>
#import <QuartzCore/CALayer.h>
#define OBJECT_ARG(TYPE, ARG, NAME) TYPE *NAME = (__bridge TYPE *)((void*)to_int(datas[ARG]));

bool alert_clicked = false;

bool ya_set_scroll_pos_lock = false;

void send_js_callback(char *name, id sender) {
	int O = (int)sender;
	NSString *SCRIPT = [[NSArray arrayWithObjects:
		@"yaui.on.", cp_str(name) ,@"(", cp_str(cp_int(O)), @");", nil] componentsJoinedByString:@""];
	char *s = (char*)[SCRIPT UTF8String];
//	NSLog(@"%i> CALLING: %s\n", (int)getTickCount(), s);
	call_cpp(5, s, name);
//	NSLog(@"%i> DONE: %s\n", (int)getTickCount(), s);
}

int distance(CGPoint a, CGPoint b) {
   return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int touches_distance(UIEvent *event, id self) {
   NSSet *allTouches = [event allTouches];
   if (allTouches.count == 2) {
      UITouch *touch1 = [[allTouches allObjects] objectAtIndex:0];
      UITouch *touch2 = [[allTouches allObjects] objectAtIndex:1];
      CGPoint xy1 = [touch1 locationInView:self];
      CGPoint xy2 = [touch2 locationInView:self];
      return distance(xy1, xy2);
   }
   return -1;
}

@interface MYScrollView : UIScrollView { @public bool vert; } @end;
@implementation MYScrollView @end

@implementation MYLabel @end
@implementation MYButton @end
@implementation MYInput @end
int last_fs;
@implementation MYEdit 
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *) event {
   start_distance = touches_distance(event, self);
}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *) event {
   start_distance = -1;
   start_font_size = last_fs;
}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *) event {
   if (start_distance > 0) {
      int d = touches_distance(event, self);
      if (d > 0) {
         int newf = ((double)start_font_size / (double)start_distance) * d;
         if (newf != start_font_size) {
            last_fs = newf;
            [self setFont:[UIFont fontWithName:@"HanaMinB" size:newf]];
         }
      }
   }
}

@end

#define SCREEN_SIZE_IPHONE_CLASSIC 3.5
#define SCREEN_SIZE_IPHONE_TALL 4.0
#define SCREEN_SIZE_IPAD_CLASSIC 9.7

CGFloat screenPhysicalSize() {
   if(true)//UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
   {
      CGSize result = [[UIScreen mainScreen] bounds].size;
      if (result.height < 500) return SCREEN_SIZE_IPHONE_CLASSIC;  // iPhone 4S / 4th Gen iPod Touch or earlier
      else return SCREEN_SIZE_IPHONE_TALL;  // iPhone 5
   }
   else return SCREEN_SIZE_IPAD_CLASSIC; // iPad
}

//@interface AppDelegate : UIResponder <UIApplicationDelegate>
//@property (strong, nonatomic) UIWindow *window;

//@end
//void go();

CGRect PLACE(char *xywh) {
	NSString *s = [NSString stringWithUTF8String: xywh];
	NSArray *A = [s componentsSeparatedByString:@":"];
	return CGRectMake(
		[A[0] intValue], 
		[[A objectAtIndex: 1] intValue], 
		[[A objectAtIndex: 2] intValue], 
		[[A objectAtIndex: 3] intValue]);
}
	

@implementation MYWindow
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
   [self endEditing:YES];
}
@end

@implementation ViewController

- (void)viewDidLoad
{
   [super viewDidLoad];
//   [self make_scroller_sample_h]; return;
   call_cpp(1, 0, 0);
   NSString *appFolderPath = [[NSBundle mainBundle] resourcePath];
   set_DOCDIR([appFolderPath UTF8String]);
   call_cpp(4, "bootstrap.js", 0);
//   self.view.layer.borderColor = [UIColor redColor].CGColor;
//   self.view.layer.backgroundColor = [UIColor colorWithRed:0 green:.7 blue:.7 alpha:1].CGColor;
   self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"paper.jpg"]];
	// TEMPORAL BELOW
	UITextView* T = [[UITextView alloc] initWithFrame:PLACE("0:600:300:100")];
	T.text = @"nothing yet2";
	call_cpp(5, "function five() { return 5555 }; print(five() + 2)", 0);
	[self.view addSubview:T];
}

- (void)didReceiveMemoryWarning
{ 
   [super didReceiveMemoryWarning];
   // Dispose of any resources that can be recreated.
}

-(void)scroll_button_click: (id) sender
{
	MYButton *B = (MYButton *)sender;
	UIAlertView *someError = [[UIAlertView alloc]
		initWithTitle: @"Alert" message: B.currentTitle
		delegate: self cancelButtonTitle: @"Ok" otherButtonTitles: nil];
	[someError show];
}

-(void)alert_click
{
	alert_clicked = true;
}

-(void)event_dispatcher2: (id) sender
{
	const char* C = class_getName([sender class]);
}

-(void)event_dispatcher: (id) sender
{
	NSString *CB = 0;
	if ([sender isKindOfClass:[UIButton class]]) {
		CB = @"yaui.on.button";
	}
	if ([sender isKindOfClass:[UITextField class]]) {
		CB = @"yaui.on.text_change";
	}
	if (CB.length > 0) {
		NSString *SENDER = [[NSNumber numberWithInt:(int)sender] stringValue];
		NSString *SCRIPT = [[NSArray arrayWithObjects:
			CB,  @"(",  SENDER,  @");"
			, nil] componentsJoinedByString:@""];
		char *s = (char*)[SCRIPT UTF8String];
		call_cpp(5, s, s);
	}
}

-(void) timer_dispatcher: (NSTimer *) T {
	char *id = [[T userInfo] UTF8String];
//	printf("timer dispatcher: %s\n", id);
	NSString *SCRIPT = [[NSArray arrayWithObjects:
			@"yaui.on.timer(", [T userInfo], @");", nil] componentsJoinedByString:@""];
	char *s = (char*)[SCRIPT UTF8String];
	call_cpp(5, s, (char*)0);
}

- (BOOL)textViewShouldBeginEditing:(UITextField *)textField {
	[GLOBAL_W endEditing:YES];
	return NO;
}

- (void)textViewDidBeginEditing:(UITextField *)textField {
	return;
}

- (BOOL)textFieldShouldReturn:(UITextField *)theTextField {
	[GLOBAL_W endEditing:YES];
	return YES;
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
	NSLog(@"objc: subview_scroll_begin\n");
	send_js_callback("subview_scroll_begin", scrollView);
//	printf("%i> scrollViewWillBeginDragging\n", (int)getTickCount());
}

- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset {
//	int X = scrollView.contentOffset.x;
//	[scrollView setContentOffset:CGPointMake(X, 0) animated:NO];
	NSLog(@"objc: subview_scroll_end\n");
	send_js_callback("subview_scroll_end", scrollView);
	*targetContentOffset = scrollView.contentOffset;
}

//- (void)scrollViewWillBeginDecelerating:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset {
//	NSLog(@"objc: Trying to stop deceleration!\n");
//	[scrollView setContentOffset:scrollView.contentOffset animated:NO];
//}


@end


const
ya_flag_ = 0x100,
ya_flag_parent = 0x200,
ya_flag_view = 0x400,
ya_flag_textview = 0x800,
ya_main_handle          = 0,
ya_alert                = 1,
ya_make_button          = 2 + ya_flag_parent,
ya_make_label           = 3 + ya_flag_parent,
ya_make_input           = 4 + ya_flag_parent,
ya_make_edit            = 5 + ya_flag_parent,
ya_make_image           = 6 + ya_flag_parent,
ya_make_hview           = 7 + ya_flag_parent,
ya_make_vview           = 8 + ya_flag_parent,
ya_hide                 = 9 + ya_flag_view,
ya_show                 = 10 + ya_flag_view,
ya_input_line           = 11 + ya_flag_textview,
ya_text_of_text         = 12 + ya_flag_textview,
ya_set_text             = 13 + ya_flag_textview,
ya_set_font             = 14 + ya_flag_textview,
ya_set_read_only        = 15 + ya_flag_textview,
ya_set_scroll_area      = 16 + ya_flag_view,
ya_set_scroll_pos       = 17 + ya_flag_view,
ya_set_bgcolor          = 18 + ya_flag_view,
ya_set_xywh             = 19 + ya_flag_view,
ya_get_app_size         = 20,
ya_get_scroll_pos       = 21 + ya_flag_view,
ya_set_timeout          = 22; 

char *code_toString(int code) {
		if (code == ya_main_handle) return "ya_main_handle";
		if (code == ya_alert) return "ya_alert";
		if (code == ya_make_button) return "ya_make_button";
		if (code == ya_make_label) return "ya_make_label";
		if (code == ya_make_input) return "ya_make_input";
		if (code == ya_make_edit) return "ya_make_edit";
		if (code == ya_make_image) return "ya_make_image";
		if (code == ya_make_hview) return "ya_make_hview";
		if (code == ya_make_vview) return "ya_make_vview";
		if (code == ya_hide) return "ya_hide";
		if (code == ya_show) return "ya_show";
		if (code == ya_input_line) return "ya_input_line";
		if (code == ya_text_of_text) return "ya_text_of_text";
		if (code == ya_set_text) return "ya_set_text";
		if (code == ya_set_font) return "ya_set_font";
		if (code == ya_set_read_only) return "ya_set_read_only";
		if (code == ya_set_scroll_area) return "ya_set_scroll_area";
		if (code == ya_set_scroll_pos) return "ya_set_scroll_pos";
		if (code == ya_set_bgcolor) return "ya_set_bgcolor";
		if (code == ya_set_xywh) return "ya_set_xywh";
		if (code == ya_get_app_size) return "ya_get_app_size";
		if (code == ya_get_scroll_pos) return "ya_get_scroll_pos";
		if (code == ya_set_timeout) return "ya_set_timeout";
		return "unknown code";
}

//#import "gloss.h"

char* control_ui(int code, char** datas) {
//NSLog(@"control_ui(%i:%s)", code, code_toString(code));
	if (code == 5555) {
		NSString *s = [[NSArray arrayWithObjects:
			@"#yaui# ", cp_str(datas[0]), nil] componentsJoinedByString:@""];	
		NSLog(s);
	}
   if (code == ya_main_handle) { // RETURN MAIN VIEW JAVASCRIPT ID
      return cp_ptr(GLOBAL_VC.view);
   }
   if (code == ya_make_button) {
		OBJECT_ARG(UIView, 0, V);
		MYButton *B = [[MYButton alloc] initWithFrame:PLACE("0:0:0:0")];
		B.hidden = YES;
		[V addSubview:B];
		[B addTarget:GLOBAL_VC action:@selector(event_dispatcher:) forControlEvents:UIControlEventTouchUpInside];
		B.backgroundColor = [UIColor colorWithRed:0 green:.7 blue:.7 alpha:1];
		B.layer.borderColor = [UIColor colorWithRed:0 green:0.0 blue:0.0 alpha:0.99].CGColor;
		B.layer.borderWidth = 0.8f;
		// Draw a custom gradient -------------

		CAGradientLayer *g = [CAGradientLayer layer];
			g.frame = B.bounds;
			g.colors = [NSArray arrayWithObjects:
				#include "gloss.h"
				nil];
			[B.layer insertSublayer:g atIndex:0];
			B->g = g;
		// Rounded corners
		CALayer *btnLayer = [B layer];
			[btnLayer setMasksToBounds:YES];
			[btnLayer setCornerRadius:10.0f];      
		return cp_ptr(B);
   }
	
   if (code == ya_make_label) {
		OBJECT_ARG(UIView, 0, V);
		MYLabel *L = [[MYLabel alloc] initWithFrame:PLACE("0:0:0:0")];
		[V addSubview:L];
		[L setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:0]]; // bugofeature of ios, default label has white bg, we make transparent
		// IOS 6 only
			L.layer.shadowColor = [UIColor blackColor].CGColor;
			L.layer.shadowOpacity = 0.6;
			L.layer.shadowOffset = CGSizeMake(3,3);
			L.layer.shadowRadius = 3;
      return cp_ptr(L);
   }

	if (code == ya_set_xywh) {
		OBJECT_ARG(UIView, 0, O);
		O.frame = PLACE(datas[1]);
		if ([O isKindOfClass:[UIButton class]]) {
			OBJECT_ARG(MYButton, 0, B);
			B->g.frame = B.bounds;
		}
		if ([O isKindOfClass:[MYScrollView class]]) {
			// We want height of hview's child be the same as hview
			OBJECT_ARG(MYScrollView, 0, S);
			S.contentSize =  CGSizeMake(S.contentSize.width, O.frame.size.height);
		}

	}

	if (code == ya_set_text) {
		OBJECT_ARG (MYLabel, 0, O)
		if ([O isKindOfClass:[MYButton class]]) {
			OBJECT_ARG(MYButton, 0, B);
			[B setTitle:cp_str(datas[1]) forState:UIControlStateNormal];
		} else O.text = cp_str(datas[1]);
	}

	//NSString* S = [U description]; // that's how you print color
	
	if (code == ya_set_font) {
		OBJECT_ARG (UIView, 0, O)
		NSArray *A = [cp_str(datas[3]) componentsSeparatedByString:@":"];
		UIColor *U = [UIColor colorWithRed:
			[[A objectAtIndex: 0] doubleValue] 
			green:[[A objectAtIndex: 1] doubleValue] 
			blue:[[A objectAtIndex: 2] doubleValue] 
			alpha:[[A objectAtIndex: 3] doubleValue]];
		if ([O isKindOfClass:[MYButton class]]) {
			OBJECT_ARG(MYButton, 0, B);
			[B.titleLabel setFont:[UIFont fontWithName:cp_str(datas[1]) size:to_int(datas[2])]];
			[B setTitleColor:U forState:UIControlStateNormal];
			[B setTitleColor:U forState:UIControlStateHighlighted];
		} else 
		if ([O isKindOfClass:[MYLabel class]]) {
			OBJECT_ARG(MYLabel, 0, B);
			[B setFont:[UIFont fontWithName:cp_str(datas[1]) size:to_int(datas[2])]];
			B.textColor = U;
		} else 
		if ([O isKindOfClass:[MYInput class]]) {
			OBJECT_ARG(MYInput, 0, B);
			[B setFont:[UIFont fontWithName:cp_str(datas[1]) size:to_int(datas[2])]];
			B.textColor = U;
		} else 
		if ([O isKindOfClass:[MYEdit class]]) {
			OBJECT_ARG(MYEdit, 0, B);
			[B setFont:[UIFont fontWithName:cp_str(datas[1]) size:to_int(datas[2])]];
			B.textColor = U;
		} else ;
	}
	if (code == ya_show) { OBJECT_ARG(UIView, 0, V); V.hidden = NO; }
	if (code == ya_hide) { OBJECT_ARG(UIView, 0, V); V.hidden = YES; }
	if (code == ya_get_app_size) {
		CGRect screenRect = [[UIScreen mainScreen] bounds];
		CRET = [NSString stringWithFormat:@"%f:%f",  screenRect.size.width,  screenRect.size.height];
		return (char*)[CRET UTF8String];
	}
	if (code == ya_text_of_text) {
		// get text of input/edit (not other! no button, no label)
		OBJECT_ARG (MYInput, 0, O)
		CRET = O.text;
		return (char*)[CRET UTF8String];
	}

	if (code == ya_make_input) {
		OBJECT_ARG(UIView, 0, V);
		MYInput* T = [[MYInput alloc] initWithFrame:PLACE("0:0:0:0")];
		[V addSubview:T];
//		[T setDelegate:GLOBAL_VC];
		[T addTarget:GLOBAL_VC action:@selector(event_dispatcher:) forControlEvents:UIControlEventEditingChanged];
		//	[[NSNotificationCenter defaultCenter] addObserver:GLOBAL_VC
		//selector:@selector(event_dispatcher2:)
		//name:UITextFieldTextDidEndEditingNotification
		//object:T];
		[T setBackgroundColor:[UIColor colorWithRed:1 green:1 blue:1 alpha:1]];
		CALayer *btnLayer = [T layer];
		[btnLayer setMasksToBounds:YES];
		[btnLayer setCornerRadius:5.0f];
		return cp_ptr(T);
	}
	if (code == ya_make_edit) {
		OBJECT_ARG(UIView, 0, V);
		MYEdit* T = [[MYEdit alloc] initWithFrame:PLACE("0:0:0:0")];
		[V addSubview:T];
		T.multipleTouchEnabled = YES;
		CALayer *btnLayer = [T layer];
		[btnLayer setMasksToBounds:YES];
		[btnLayer setCornerRadius:5.0f];
		//NO SUCH THING AS ONCHANGE FOR TEXT EDIT!
		//[T addTarget:MAIN_OBJECT action:@selector(event_dispatcher:) forControlEvents:UIControlEventEditingChanged];
		return cp_ptr(T);
	}
	if (code == ya_set_read_only) {
		OBJECT_ARG(MYEdit, 0, T);
		[T setDelegate:GLOBAL_VC];
	}
	if (code == ya_make_image) {
		OBJECT_ARG(UIView, 0, V);
		UIImageView *I = [[UIImageView alloc] initWithFrame:PLACE("0:0:0:0")];
		[V addSubview:I];
		I.image = [UIImage imageNamed:cp_str(datas[1])];
		return cp_ptr(I);
	}
	if (code == ya_make_hview) {
		OBJECT_ARG(UIView, 0, V);
		MYScrollView *S = [[MYScrollView alloc] initWithFrame:PLACE("0:0:0:0")];
		S->vert = false;
		[S setDelegate:GLOBAL_VC];
		//S.contentSize = CGSizeMake(55, 55);
		//S.backgroundColor = [UIColor colorWithRed:1 green:1 blue:1 alpha:0.0];
		S.bounces = NO;
		[V addSubview:S];
		return cp_ptr(S);
	}
	if (code == ya_make_vview) {
		OBJECT_ARG(UIView, 0, V);
		MYScrollView *S = [[MYScrollView alloc] initWithFrame:PLACE("0:0:0:0")];
		S->vert = true;
		[S setDelegate:GLOBAL_VC];
		S.bounces = NO;
		[V addSubview:S];
		return cp_ptr(S);
	}
	if (code == ya_set_scroll_area) {
		OBJECT_ARG(MYScrollView, 0, V);
		if (V->vert)
		V.contentSize =  CGSizeMake(V.contentSize.width, to_int(datas[1]));
		else V.contentSize =  CGSizeMake(to_int(datas[1]), V.contentSize.height);
	}
	if (code == ya_set_scroll_pos) {
		OBJECT_ARG(MYScrollView, 0, V);
		int N = to_int(datas[1]);
		if (V->vert)
		[V setContentOffset:CGPointMake(0, N) animated:NO];
		else [V setContentOffset:CGPointMake(N, 0) animated:NO];
	} 
	if (code == ya_get_scroll_pos) {
		OBJECT_ARG(MYScrollView, 0, S);
		int N; if (S->vert) N = S.contentOffset.y; else N = S.contentOffset.x;
		return cp_int(N);
	}
	if (code == ya_set_timeout) {
		double T = to_dbl(datas[1]) / 1000;
//		printf("set(%s) %i\n", datas[0], (int) (T * 1000));
		if (T == 0) return "Undefined";
		[NSTimer scheduledTimerWithTimeInterval:
				T
				target: GLOBAL_VC 
				selector: @selector(timer_dispatcher:) 
				userInfo: cp_str(datas[0])
				repeats: NO];
		//[timer invalidate];
	}

// -----------------------------------------------------
// --
// --
// -- version split
// --
// --
// -----------------------------------------------------

	if (code == 1) { // ALERT FUCTION
		UIAlertView *someError = [[UIAlertView alloc]
		initWithTitle: @"Alert" message: cp_str(datas[0])
		delegate: GLOBAL_VC cancelButtonTitle: @"Ok" otherButtonTitles: nil];
		[someError show];
	}
   if (code == 2) { // HIDE INPUT KEYBOARD
      [GLOBAL_W endEditing:YES];
   }
   if (code == 11) { // SET BACK COLOR FOR ANY OBJECT
      OBJECT_ARG (MYLabel, 0, O)
      NSString *s = cp_str(datas[1]);
      NSArray *A = [s componentsSeparatedByString:@":"];
      [O setBackgroundColor:[UIColor colorWithRed:[[A objectAtIndex: 0] intValue] green:[[A objectAtIndex: 1] intValue] blue:[[A objectAtIndex: 2] intValue] alpha:[[A objectAtIndex: 3] intValue]]];
   }

   return "Undefined";
}


@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
   GLOBAL_AD = self;
   self.window = [[MYWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
   GLOBAL_W = (MYWindow*)self.window;
   self.viewController = [ViewController alloc];
   GLOBAL_VC = self.viewController;
   self.window.rootViewController = self.viewController;
   [self.window makeKeyAndVisible];
   self.window.backgroundColor = [UIColor lightGrayColor];
   return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application{}
- (void)applicationDidEnterBackground:(UIApplication *)application{}
- (void)applicationWillEnterForeground:(UIApplication *)application{}
- (void)applicationDidBecomeActive:(UIApplication *)application{}
- (void)applicationWillTerminate:(UIApplication *)application{}

@end

/*@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor brownColor];
// blackColor darkGrayColor lightGrayColor whiteColor grayColor redColor greenColor blueColorcyanColor yellowColor magentaColor orangeColor purpleColor brownColor clearColor	 
    [self.window makeKeyAndVisible];
    return YES;
}
- (void)applicationWillResignActive:(UIApplication *)application {}
- (void)applicationDidEnterBackground:(UIApplication *)application {}
- (void)applicationWillEnterForeground:(UIApplication *)application {}
- (void)applicationDidBecomeActive:(UIApplication *)application {}
- (void)applicationWillTerminate:(UIApplication *)application {}
@end
*/

int main(int argc, char *argv[])
{
 @autoreleasepool {
     return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
 }
}
//end

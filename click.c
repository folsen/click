#include <ApplicationServices/ApplicationServices.h>
#include <unistd.h>
#include <time.h>

int main() {
  // Where we want to click
  int x = 800;
  int y = 200;

  // Move there (just for visual help)
  CGEventRef move = CGEventCreateMouseEvent(
    NULL, kCGEventMouseMoved,
    CGPointMake(x, y),
    kCGMouseButtonLeft // ignored
  );
  // Left button down
  CGEventRef click_down = CGEventCreateMouseEvent(
    NULL, kCGEventLeftMouseDown,
    CGPointMake(x, y),
    kCGMouseButtonLeft
  );
  // Left button up
  CGEventRef click_up = CGEventCreateMouseEvent(
    NULL, kCGEventLeftMouseUp,
    CGPointMake(x, y),
    kCGMouseButtonLeft
  );

  // The delay we want between clicks in nanoseconds
  struct timespec tim, tim2;
  tim.tv_sec = 0;
  tim.tv_nsec = 100000000L;

  // Click 1000 times with a delay in between
  for (int i = 0; i<1000; i++) {
    CGEventPost(kCGHIDEventTap, move);
    nanosleep(&tim, &tim2);
    CGEventPost(kCGHIDEventTap, click_down);
    CGEventPost(kCGHIDEventTap, click_up);
  }

  // Release the events
  CFRelease(click_up);
  CFRelease(click_down);
  CFRelease(move);

  return 0;
}

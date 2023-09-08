use winit::event::{Event, WindowEvent};
use winit::event_loop::{ControlFlow, EventLoop};
use winit::window::WindowBuilder;

fn main() {
    init_logger();

    let event_loop = EventLoop::new();
    let window = WindowBuilder::new()
        .build(&event_loop).unwrap();

    event_loop.run(move |event, _, control_flow| {
        match event {
            Event::NewEvents(_) => {}
            Event::WindowEvent {
                ref event,
                window_id
            } => {
                if window_id == window.id() && event == &WindowEvent::CloseRequested {
                    *control_flow = ControlFlow::Exit;
                }
            }
            Event::DeviceEvent { .. } => {}
            Event::UserEvent(_) => {}
            Event::Suspended => {}
            Event::Resumed => {}
            Event::MainEventsCleared => {}
            Event::RedrawRequested(_) => {
                // Draw stufff
            }
            Event::RedrawEventsCleared => {
                window.request_redraw();
            }
            Event::LoopDestroyed => {}
        }
    })
}

fn init_logger() {
    cfg_if::cfg_if! {
        if #[cfg(target_arch = "wasm32")] {
            std::panic::set_hook(Box::new(console_error_panic_hook::hook));
            console_log::init_with_level(log::Level::Warn).expect("Couldn't initialize logger");
        } else {
            env_logger::init();
        }
    }
}

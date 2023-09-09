use winit::event::{Event, WindowEvent};
use winit::event_loop::{ControlFlow, EventLoop};
use winit::window::{Window, WindowBuilder};

use crate::engine::app::BloomApplication;
use crate::engine::renderer::Renderer;

pub mod app;
pub mod renderer;

pub struct BloomEngine;

impl BloomEngine {
    pub async fn run_app(mut app: impl BloomApplication + 'static) {
        Self::initialise_logger();

        let event_loop = EventLoop::new();
        let window = Self::create_window(&event_loop);
        let mut renderer = Renderer::new(&window).await;

        app.initialise();

        event_loop.run(move |event, _, control_flow| {
            match event {
                Event::NewEvents(_) => {}
                Event::WindowEvent {
                    event: ref window_event,
                    window_id
                } => {
                    if window_id == window.id() {
                        match window_event {
                            WindowEvent::CloseRequested => { *control_flow = ControlFlow::Exit }
                            WindowEvent::Resized(physical_size) => renderer.resize(*physical_size),
                            WindowEvent::ScaleFactorChanged { new_inner_size, .. } => renderer.resize(**new_inner_size),
                            _ => {}
                        }
                    }
                }
                Event::DeviceEvent { .. } => {}
                Event::UserEvent(_) => {}
                Event::Suspended => {}
                Event::Resumed => {}
                Event::MainEventsCleared => {
                    app.update();
                }
                Event::RedrawRequested(_) => {
                    let _ = app.draw(&renderer);
                }
                Event::RedrawEventsCleared => {
                    window.request_redraw();
                }
                Event::LoopDestroyed => {
                    app.destroy();
                }
            }
        });
    }

    fn initialise_logger() {
        cfg_if::cfg_if! {
            if #[cfg(target_arch = "wasm32")] {
                std::panic::set_hook(Box::new(console_error_panic_hook::hook));
                console_log::init_with_level(log::Level::Info).expect("Couldn't initialize logger");
            } else {
                env_logger::init();
            }
        }
    }

    fn create_window(event_loop: &EventLoop<()>) -> Window {
        let mut builder = WindowBuilder::new();

        cfg_if::cfg_if! {
            if #[cfg(target_arch = "wasm32")] {
                use winit::platform::web::WindowBuilderExtWebSys;
                use web_sys::HtmlCanvasElement;
                use wasm_bindgen::JsCast;

                let canvas = web_sys::window()
                    .and_then(|window| window.document())
                    .and_then(|document| document.get_element_by_id("render-target"))
                    .and_then(|element| element.dyn_into::<HtmlCanvasElement>().ok())
                    .expect("Unable to attach to Canvas element");

                builder = builder
                    .with_canvas(Some(canvas))
                    .with_prevent_default(false);
            } else {
                use winit::dpi::LogicalSize;
                builder = builder
                    .with_inner_size(LogicalSize::new(1920, 1080))
                    .with_title("Bloom");
            }
        }

        builder.build(event_loop).unwrap()
    }
}

use wgpu::SurfaceError;
use crate::engine::app::BloomApplication;
use crate::engine::BloomEngine;
use crate::engine::renderer::Renderer;

mod engine;

struct Application;

impl BloomApplication for Application {
    fn initialise(&mut self) {
        log::info!("Starting up...")
    }

    fn destroy(&mut self) {
        log::info!("Shutting down...");
    }

    fn update(&mut self) {}

    fn draw(&mut self, renderer: &Renderer) -> Result<(), SurfaceError> {
        let output = renderer.surface.get_current_texture()?;
        let view = output.texture.create_view(&wgpu::TextureViewDescriptor::default());

        let mut encoder = renderer.device.create_command_encoder(&wgpu::CommandEncoderDescriptor {
            label: Some("Render Encoder")
        });

        encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
            label: Some("Render Pass"),
            color_attachments: &[Some(wgpu::RenderPassColorAttachment {
                view: &view,
                resolve_target: None,
                ops: wgpu::Operations {
                    load: wgpu::LoadOp::Clear(wgpu::Color {
                        r: 0.1,
                        g: 0.2,
                        b: 0.3,
                        a: 1.0,
                    }),
                    store: true,
                },
            })],
            depth_stencil_attachment: None,
        });

        renderer.queue.submit(std::iter::once(encoder.finish()));
        output.present();
        Ok(())
    }
}

#[cfg(not(target_arch = "wasm32"))]
fn main() {
    pollster::block_on(BloomEngine::run_app(Application));
}

#[cfg(target_arch = "wasm32")]
#[wasm_bindgen::prelude::wasm_bindgen(main)]
pub async fn main() {
    BloomEngine::run_app(Application).await;
}
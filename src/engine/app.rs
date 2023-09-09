use wgpu::SurfaceError;

use crate::engine::renderer::Renderer;

pub trait BloomApplication {
    fn initialise(&mut self);
    fn destroy(&mut self);
    fn update(&mut self);
    fn draw(&mut self, renderer: &Renderer) -> Result<(), SurfaceError>;
}

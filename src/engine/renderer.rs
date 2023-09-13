use wgpu::*;
use winit::dpi::PhysicalSize;
use winit::window::Window;

pub struct Renderer {
    pub surface: Surface,
    pub device: Device,
    pub queue: Queue,
    pub surface_configuration: SurfaceConfiguration,
    pub render_pipeline: RenderPipeline,
}

impl Renderer {
    pub async fn new(window: &Window) -> Renderer {
        let size = window.inner_size();

        let instance = Instance::new(InstanceDescriptor {
            backends: Backends::PRIMARY,
            dx12_shader_compiler: Default::default(),
        });

        let surface = Self::create_surface(window, &instance).await;
        let adapter = Self::select_adapter(&instance, &&surface).await;
        let (device, queue) = Self::create_device_and_queue(&adapter).await;
        let surface_configuration =
            Self::create_surface_configuration(&device, &adapter, &surface, size);

        let shader = device.create_shader_module(include_wgsl!("shaders/default.wgsl"));
        let render_pipeline =
            Self::create_render_pipeline(&device, &shader, &surface_configuration);

        Renderer {
            surface,
            device,
            queue,
            surface_configuration,
            render_pipeline,
        }
    }

    async fn create_surface(window: &Window, instance: &Instance) -> Surface {
        unsafe { instance.create_surface(window) }.unwrap()
    }

    async fn select_adapter(instance: &Instance, surface: &&Surface) -> Adapter {
        instance
            .request_adapter(&RequestAdapterOptions {
                power_preference: PowerPreference::HighPerformance,
                compatible_surface: Some(surface),
                force_fallback_adapter: false,
            })
            .await
            .unwrap()
    }

    async fn create_device_and_queue(adapter: &Adapter) -> (Device, Queue) {
        adapter
            .request_device(
                &DeviceDescriptor {
                    features: Features::empty(),
                    limits: Limits::default(),
                    label: None,
                },
                None,
            )
            .await
            .unwrap()
    }

    fn create_surface_configuration(
        device: &Device,
        adapter: &Adapter,
        surface: &Surface,
        size: PhysicalSize<u32>,
    ) -> SurfaceConfiguration {
        let surface_capabilities = surface.get_capabilities(adapter);
        let surface_format = surface_capabilities
            .formats
            .iter()
            .copied()
            .find(|format| format.is_srgb())
            .unwrap_or(surface_capabilities.formats[0]);

        let surface_configuration = SurfaceConfiguration {
            usage: TextureUsages::RENDER_ATTACHMENT,
            format: surface_format,
            width: size.width,
            height: size.height,
            present_mode: PresentMode::AutoVsync,
            alpha_mode: CompositeAlphaMode::Auto,
            view_formats: vec![],
        };

        surface.configure(device, &surface_configuration);

        surface_configuration
    }

    fn create_render_pipeline(
        device: &Device,
        shader: &ShaderModule,
        surface_configuration: &SurfaceConfiguration,
    ) -> RenderPipeline {
        let pipeline_layout = device.create_pipeline_layout(&PipelineLayoutDescriptor {
            label: Some("Render Pipeline Layout"),
            bind_group_layouts: &[],
            push_constant_ranges: &[],
        });

        device.create_render_pipeline(&RenderPipelineDescriptor {
            label: Some("Render Pipeline"),
            layout: Some(&pipeline_layout),
            vertex: VertexState {
                module: shader,
                entry_point: "vs_main",
                buffers: &[],
            },
            fragment: Some(FragmentState {
                module: shader,
                entry_point: "fs_main",
                targets: &[Some(ColorTargetState {
                    format: surface_configuration.format,
                    blend: Some(BlendState::REPLACE),
                    write_mask: ColorWrites::ALL,
                })],
            }),
            primitive: PrimitiveState {
                topology: PrimitiveTopology::TriangleList,
                strip_index_format: None,
                front_face: FrontFace::Ccw,
                cull_mode: Some(Face::Back),
                polygon_mode: PolygonMode::Fill,
                unclipped_depth: false,
                conservative: false,
            },
            depth_stencil: None,
            multisample: MultisampleState {
                count: 1,
                mask: !0,
                alpha_to_coverage_enabled: false,
            },
            multiview: None,
        })
    }

    pub fn resize(&mut self, new_size: PhysicalSize<u32>) {
        if new_size.width > 0 && new_size.height > 0 {
            self.surface_configuration.width = new_size.width;
            self.surface_configuration.height = new_size.height;
            self.surface
                .configure(&self.device, &self.surface_configuration);
        }
    }
}

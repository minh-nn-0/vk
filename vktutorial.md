

# STEPS
1. VkInstance and VkPhysicalDevice
- Describe any extensions will be using, 
  can query supported hardware,
  can query properties like VRAM size and capabilities to select
2. VkDevice (logical device)
- Describe with VkPhysicalDeviceFeatures

- Specify Queue families

3. Window surface and swap chain
- Window with GLFW
- Window Surface (VkSurfaceKHR) and swapchain (VkSwapchainKHR)

- Swapchain provides complete image to show to the screen.
  Basic purpose is to ensure that the image currently rendering is diferrent
  from one that currently on screen.
  Present mode can be double buffering (vsync) and triple buffering

4. Image views and framebuffers
- To draw to an image from the swap chain, we have to wrap it to a VkImageView and VkFrameBuffer 
- Imageview references to specific part of an image
- Framebuffer references image views that are to be used for color, depth, stencil targets.

5. Render passes
- Describe the type of images that are used during rendering operations
- render pass only describes the type, *VkFrameBuffer* actually binds specific images to these slots

6. Graphics pipeline

- VkPipeline describe the configurable state of the graphics card
- Almost all configuration to graphics pipeline need to be set in advanced <- compile time

7. Command pools

- Many operations need to be submitted to a queue. Theses operations need to be recorded into 
a VkCommandBuffer before they can be submitted. These commands buffers are allocated from 
a VkCommandPool that is associated with specific queue family.
to draw a triangle:
    - begin render pass
    - bind graphics pipeline
    - draw 3 vertices
    - end render pass

8. Main loop



"
So in short, to draw the first triangle we need to:

    Create a VkInstance
    Select a supported graphics card (VkPhysicalDevice)
    Create a VkDevice and VkQueue for drawing and presentation
    Create a window, window surface and swap chain
    Wrap the swap chain images into VkImageView
    Create a render pass that specifies the render targets and usage
    Create framebuffers for the render pass
    Set up the graphics pipeline
    Allocate and record a command buffer with the draw commands for every possible swap chain image
    Draw frames by acquiring images, submitting the right draw command buffer and returning the images back to the swap chain
"



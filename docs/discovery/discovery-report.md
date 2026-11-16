# Discovery report

## Problem statement

Build a maintainable, extensible, CPU-based C++ ray tracer that renders scenes and animations created in third-party software, providing useful previews for designers and reliable final images for animated-film production.

## Client interview summary

### 1. Scene preparation and rendering workflow

**Need:** Render scenes and animations created by designers in third-party software, without building a scene-authoring application.

**Q01** (classmate): "How will designers prepare scenes, and how will they use the ray tracer?"

**A:** Designers create the scene or animation on their desktop using third-party software. They save it as a file, which the ray tracer takes as input to produce previews and final rendered images. No interface is required.

**My conclusion:** The project's main responsibility is rendering externally authored scenes, not modelling or animation creation. The input format and export workflow are essential integration decisions. "No interface" should be clarified: the client may mean no graphical interface rather than no way to control rendering.

### 2. Preview rendering and final image quality

**Need:** Provide designers with quick, sufficiently accurate previews and produce high-quality final images.

**Q02** (classmate): "What do designers need from previews compared with final renders?"

**A:** Designers need images quickly and accurately while working. Final rendering needs high quality. At least 10 pre-renders per image are wanted before the final render.

**My conclusion:** The renderer must support both iteration and final production. Configurable quality settings are a possible implementation approach, not a client-specified solution. Preview speed and final image quality do not yet have measurable acceptance criteria.

### 3. Production workload and rendering deadline

**Need:** Support the studio's animated-film workload within its production window.

**Q03** (classmate): "What film length, frame rate, resolution, and rendering window should we plan for?"

**A:** Mainly fully animated films, lasting 90 minutes at 24 frames per second in HD. Once the design stage is complete, final rendering should take no more than two months. The studio has 200 machines.

**My conclusion:** One complete final-render pass represents 129,600 frames, excluding previews, revisions, and retries. A meaningful performance target also needs the exact resolution, representative scenes, machine specifications, and available computing time. The two-month deadline cannot yet be translated into a reliable per-frame rendering budget.

### 4. CPU execution and deployment environments

**Need:** Run rendering on the studio's available CPU hardware.

**Q04** (classmate): "What hardware is available, and where will rendering run?"

**A:** Designers have desktop machines, and there is a separate production-rendering context. The studio does not have graphics cards for rendering, so ray tracing must run on CPUs.

**My conclusion:** Required rendering functionality must work without a GPU. Both desktop preview use and production execution need consideration, but their operating systems, hardware specifications, and submission workflow remain unknown.

### 5. Image reliability and diagnosis

**Need:** Produce trustworthy images and make rendering defects understandable to the technical team.

**Q05** (classmate): "What happened the last time a render went wrong?"

**A:** Black artifacts appeared in the rendered image, and the engineering team could not identify the cause.

**Q06** (classmate): "What do you need when a rendering problem occurs?"

**A:** The software must produce reliable images. If there is a problem, the team must be able to work out where it comes from.

**My conclusion:** Successful image generation alone is insufficient; diagnosability also matters. The previous defective scene would be valuable evidence for testing if the studio can provide it. Diagnostic logs, saved render settings, and reproducible test cases are possible approaches requiring further agreement.

### 6. Long-term maintenance and documentation

**Need:** Allow the studio's technical team to maintain the renderer without depending on its original author.

**Q07** (classmate): "Who will maintain the software, and what maintenance problems have you experienced?"

**A:** Maintenance and responsibility will remain in-house over the long term. The technical team has five members. The person who wrote the existing software has left, and the remaining team cannot debug or maintain it effectively.

**Q08** (classmate): "Is a particular documentation format required?"

**A:** No specific documentation format is required.

**My conclusion:** Knowledge transfer and understandable code are central to the project. The lack of a prescribed documentation format does not mean documentation is unnecessary. A proposed acceptance check is that another team member can build, run, investigate, and modify the renderer using the delivered materials; this still needs client agreement.

### 7. Ownership, licensing, and extensibility

**Need:** Give the studio control over the renderer and the ability to add capabilities as project requirements evolve.

**Q09** (classmate): "Why do you want your own software instead of continuing with the current tools?"

**A:** Maya licensing is expensive, and it does not satisfy all the studio's needs. The studio wants its own open-source software so it can add features.

**Q10** (classmate): "What should the renderer support initially and later?"

**A:** Ray tracing is the current priority. Requirements change between projects, and more effects should be possible later.

**My conclusion:** Modification rights and extensibility matter alongside initial functionality. However, building a renderer should not be assumed to replace the third-party application used for scene creation. The meaning of "open source," the intended licence, and the initial feature boundary remain unresolved.

### 8. Image output and storage

**Need:** Save rendered images in a location accessible to the studio's workflow.

**Q11** (me): "Where should rendered images be stored?"

**A:** Generated PNG images will be stored locally on the machines, with a shared drive. Partner studios should also be able to test and run the software.

**My conclusion:** PNG is the latest specific output format recorded, although the client initially said there was no required format. The relationship between local storage, the shared drive, and partner access needs clarification. Image storage and software distribution are separate concerns.

### 9. Partner contributions

**Need:** Allow partner studios to contribute through an agreed process.

**Q12** (me): "Are there rules for contributions from partner studios?"

**A:** No rules are currently defined; establishing them is up to us.

**My conclusion:** I should propose contribution, review, testing, and release rules for approval. The client has delegated process design, but that does not automatically authorize any particular licence, access policy, or release authority.

### 10. First delivery and budget

**Need:** Deliver an agreed first version within the studio's schedule and spending expectations.

**Q13** (classmate): "When must the first version be ready, and what should it deliver?"

**A:** The first version must be ready by January 5, 2027. It should be a full ray tracer that produces reliable images.

**Q14** (classmate): "What budget is available?"

**A:** The studio would like to spend no more than €500,000 on the project.

**My conclusion:** The date and budget target are recorded, but "full ray tracer" is not a sufficiently precise delivery scope. Feasibility cannot be established until required features, acceptance scenes, hardware, and budget coverage are defined.

### 11. Constraints inherited from the original brief

The original brief requires C++ and emphasizes readable, tested, documented software. These are brief-level requirements, not additional interview answers.

**My conclusion:** They must remain traceable to the original brief rather than being attributed to classmates' questions.

### Open questions

#### Workflow and scope

- Which third-party application creates the scenes, and which export formats can it produce?
- Can the studio provide a representative input file and its expected rendered output?
- Must the renderer support complete animation files, individual frame scenes, or both?
- Does "no interface" mean no graphical interface? How should users start renders and choose settings?
- Which geometry, materials, lighting, and animation features define a "full ray tracer" for the first delivery?
- Is replacing Maya actually expected, or does the studio only intend to replace the rendering part of its workflow?

#### Performance and quality

- What exact pixel dimensions does "HD" mean?
- How long can a preview take before it disrupts a designer's work?
- What does "10 pre-renders per image" mean: every frame, selected frames, or each shot?
- Are previews included in the two-month window?
- Are all 200 machines available throughout that window?
- What are their CPU, memory, operating-system, and network specifications?
- What reference images and approval process define acceptable final quality?

#### Reliability and maintenance

- Can the studio supply the scene and settings that produced the black artifacts?
- Which failures must the team be able to diagnose, and what evidence is currently missing?
- What C++ and rendering experience does the five-person team have?
- Which maintenance tasks must team members demonstrate independently before handover?
- Who approves the software for production use?

#### Ownership and collaboration

- Does "open source" mean publicly available source code or access limited to partner studios?
- Which licence and third-party dependency rules apply?
- Who owns partner contributions and approves changes?
- How will partners obtain builds, scenes, and test results?

#### Output, schedule, and budget

- Is PNG now the agreed output format, superseding the earlier answer that no format was specified?
- What is stored locally, what is stored on the shared drive, and how do partners access it?
- Is January 5, 2027 the deadline for a prototype, a pilot, or a production-ready release?
- What costs are included in the €500,000 target?
- Is that amount a strict ceiling or a preferred budget?

## State of the art

This comparison describes solutions available today, checked on November 16, 2026. It does not assume that the fictional 2035 market conditions in the brief are current facts. Monetary prices are intentionally omitted; the pricing column records the licensing model instead.

| Solution  | Maker                                                      | Licence                                                                     | Pricing (date checked)                                                                                                                                | Capabilities                                                                                                                                                                                                                                                        | Sources                                                                        |
| --------- | ---------------------------------------------------------- | --------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| Arnold    | Autodesk                                                   | Proprietary commercial software                                             | Paid subscription; production rendering requires licensing. Amounts omitted. Checked November 16, 2026.                                               | Monte Carlo ray-tracing renderer with CPU and GPU rendering; supports production rendering of elements including hair, fur, and skin. A useful commercial reference for the CPU-rendering requirement.                                                              | Official [product overview](https://www.autodesk.com/products/arnold/overview) and [licensing documentation](https://help.autodesk.com/view/ARNOL/ENU/). |
| RenderMan | Pixar                                                      | Proprietary; commercial and restricted non-commercial licences              | Commercial licensing; non-commercial licensing is not a substitute for commercial film-production rights. Amounts omitted. Checked November 16, 2026. | Production renderer offering interactive and final-frame rendering through its XPU architecture. CPU-only suitability for the studio's exact deployment should be verified rather than assumed from its hybrid CPU/GPU description.                                 | Official [release announcement](https://renderman.pixar.com/news), [store](https://renderman.pixar.com/store), and [licence terms](https://renderman.pixar.com/eula). |
| Cycles    | Blender project and contributors                           | Apache 2.0 for the Cycles engine; Blender itself has separate GPL licensing | Open-source engine with no licence purchase required; integration and maintenance still require project resources. Checked November 16, 2026.         | Production-oriented path tracer with CPU and GPU support. Can be built as a standalone application, making it relevant to a file-input rendering workflow and source-code study.                                                                                    | Official [features page](https://www.cycles-renderer.org/), [repository](https://projects.blender.org/blender/cycles), and [Blender licence information](https://www.blender.org/about/license/). |
| pbrt-v4   | Matt Pharr, Wenzel Jakob, Greg Humphreys, and contributors | Apache 2.0                                                                  | Open-source implementation with no licence purchase required. Checked November 16, 2026.                                                              | C++ rendering system accompanying Physically Based Rendering. Supports CPU rendering, scene-file input, and advanced light-transport features. Most useful here as a documented architectural and learning reference, not as evidence of a turnkey studio pipeline. | Official [repository](https://github.com/mmp/pbrt-v4) and [project resources](https://pbrt.org/). |

### Conclusions from the comparison

- Existing renderers provide references for both commercial production workflows and open-source implementation.
  - **Arnold** demonstrates a commercial CPU-rendering option.
  - **Cycles** is especially relevant to investigating an extensible, source-available production renderer.
  - **pbrt** is valuable for understanding rendering algorithms and implementation structure.
- The next step is not to claim that a new implementation will outperform these tools. It is to agree on:
  - representative scenes,
  - required input compatibility,
  - CPU hardware,
  - quality criteria,
  - maintenance expectations.
- Those client-specific details will determine whether to build from scratch, reuse permitted components, or study an existing renderer's architecture.
- The interview establishes a need for control, reliability, and maintainability. It does not yet establish that a completely new renderer is the only way to satisfy that need.

## What is ray tracing?

Ray tracing is a way to make an image by following rays of light. For each pixel, we shoot a ray from the camera into the scene and check what object it hits first. Then we look at the light at that point: is it in shadow, does it reflect, is it transparent? To get a realistic result, we send many rays per pixel and average them. More rays means a better image but a slower render, so previews can use fewer rays and final renders more.

**Sources:** I started with [_Ray Tracing in One Weekend_](https://raytracing.github.io/), which builds a simple ray tracer step by step. The reference I would come back to is [_Physically Based Rendering_](https://pbr-book.org/4ed/contents), which goes much deeper.

## What is C++?

### Programming paradigms

C++ supports several ways of programming. You can write simple functions like in C, use classes and inheritance (object-oriented), or use templates to write code that works with different types. For a ray tracer, I think classes make sense for things like shapes and materials, and simple structs for vectors and rays.

### What to watch out for

C++ has no garbage collector, so memory has to be managed carefully (smart pointers help). Some mistakes, like reading outside an array, do not always crash and can be hard to find. Also, floating-point errors in calculations can cause visual bugs, maybe like the black artifacts the client talked about.

### Shaping the domain model

My first idea of the main parts:

- `Vec3` and `Ray` for the maths
- `Shape` (sphere, triangle…) that a ray can hit
- `Material` for how a surface reacts to light
- `Camera` to create the rays
- `Scene` to hold everything, loaded from a file
- `Renderer` to produce the image and save it as PNG

Keeping these separate should make it easier to add new features later.

**Sources:** I started with [learncpp.com](https://www.learncpp.com/). The references I would come back to are [cppreference.com](https://en.cppreference.com/w/cpp) and the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

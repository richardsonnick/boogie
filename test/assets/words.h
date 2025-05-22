#include <vector>

namespace testing {

const std::string lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas tincidunt pulvinar ipsum, a semper elit accumsan ac. Curabitur eu elit lobortis, laoreet nibh nec, lobortis dolor. Pellentesque aliquam, metus imperdiet venenatis feugiat, sem magna varius enim, ac rutrum massa arcu finibus nulla. Nulla malesuada augue quam, vel bibendum leo viverra vitae. In et lacinia neque. Curabitur auctor justo augue, at facilisis orci luctus eget. Proin nisi ante, sagittis sed lobortis id, pharetra id augue. Sed iaculis, ipsum quis dignissim rhoncus, quam mi consectetur quam, nec cursus magna mauris ac ligula. Donec efficitur egestas ligula. Aenean tempor turpis in congue vulputate. Sed pretium at nunc vel faucibus. Pellentesque iaculis interdum ante, non blandit libero sollicitudin elementum. Maecenas mollis nibh sed leo varius hendrerit. Sed pretium varius enim rhoncus tincidunt. Nulla semper urna at euismod imperdiet. Integer ut dolor nec orci commodo iaculis."
"Integer facilisis leo a erat imperdiet, non pretium mauris lacinia. Cras rutrum tincidunt tellus, dapibus consequat metus dapibus in. Praesent urna enim, interdum eget varius ut, efficitur vitae dolor. Donec interdum felis viverra nibh cursus, quis condimentum odio imperdiet. Nunc sodales quam nec erat hendrerit, sed tincidunt risus placerat. Quisque eget erat id velit facilisis convallis id non mi. Vestibulum efficitur rhoncus cursus. Suspendisse nec faucibus enim. Duis ut tellus neque. Pellentesque vulputate nisi nec turpis molestie pharetra. Praesent sed mattis purus, vitae hendrerit tortor. Interdum et malesuada fames ac ante ipsum primis in faucibus. Suspendisse mattis cursus ante sed cursus."
"Integer pulvinar auctor nunc. Donec eget ex nec lorem imperdiet fringilla sed nec elit. Fusce euismod consequat justo, id suscipit leo. Praesent in vestibulum augue, a suscipit neque. Quisque in fringilla tortor. Morbi a fermentum tortor, id dapibus massa. Fusce molestie feugiat nibh sed tempus."
"Aliquam ultricies eu neque id euismod. Aliquam fringilla nisi vel neque mollis consequat. Quisque nisi enim, aliquet ut nulla ut, mollis gravida orci. Mauris vel turpis magna. Sed ultricies mi commodo, auctor leo at, convallis diam. Nunc vestibulum ante sit amet malesuada sodales. Cras in nibh vitae ante pharetra maximus. Vivamus sit amet neque interdum, tincidunt neque eget, ultrices quam. Suspendisse rutrum egestas posuere. Etiam et ligula eget lectus congue eleifend. Maecenas quis gravida enim. Aliquam consequat dapibus mauris, non imperdiet turpis viverra vitae."
"Nullam et ex nulla. Integer laoreet dui in scelerisque condimentum. Pellentesque dictum odio sit amet consequat feugiat. Etiam sit amet nibh risus. Nunc orci lectus, convallis nec accumsan non, bibendum ut velit. Mauris molestie orci sit amet vehicula imperdiet. Donec placerat metus ex, sed consectetur sem blandit venenatis. In ultricies turpis quis ex cursus, in dictum risus pharetra. Donec pellentesque venenatis magna. Curabitur in dui nibh. Maecenas dignissim ultricies turpis, id rutrum ex vehicula vitae. Aenean posuere ligula in ipsum sollicitudin rutrum. Cras eleifend, lacus ut gravida finibus, lectus leo blandit velit, sed auctor purus augue sit amet massa.";

std::vector<std::string> test_vector = {
    "",
    "hello",
    "                    ",
    "thequickbrownfoxjumpedoverthelazydog",
    "We got a fast car.",
    "Dont-Dont u want me baby",
    "dancing in the moonlight ",
    "It's super natu ral deeeee light",
    "%#$@%@#$%^@#$%@#$%T%^TDSFASDFT$YG",
    lorem
};

}
#include "dependency/GitDependency.h"

#include <format>
#include <regex>

#include "dependency/MalformedDependencyException.h"

GitDependency::GitDependency(const std::string& data) {
    // get the git path and tag
    std::regex regex1(R"~(^(.+?\.git)(?:==(.+?))?$)~");
    // get the name
    std::regex regex2(R"~(.+\/(.+?)\/(.+?).git$)~");

    std::smatch match1, match2;

    if (std::regex_match(data, match1, regex1)) {
        git = match1[1];
        tag = "";
        if (match1.size() > 2) {
            tag = match1[2];
        }
        if (std::regex_match(git, match2, regex2)) {
            owner = match2[1];
            name = match2[2];
            return;
        }
    }

    throw MalformedDependencyException(data);
}

bool GitDependency::isSimilar(const IDependency* other) const {
    if (const GitDependency* gitOther = dynamic_cast<const GitDependency*>(other)) {
        return gitOther->git == git;
    }
    return false;
};

std::string GitDependency::toString() const {
    std::string output = git;
    if (!tag.empty()) {
        output += std::format("=={}", tag);
    }
    return output;
}

